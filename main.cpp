#include <QDebug>
#include "ta_func.h"

int main(int /*argc*/, char * /*argv*/[])
{

    if ( TA_Initialize() != TA_SUCCESS)
        return -1;

    double data[10] = {143.929993, 144.119995, 143.800003, 140.880005, 140.639999, 140.919998, 141.419998, 139.839996, 141.460007, 139.990005};
    const int data_size = sizeof(data) / sizeof(double);

    QVector<double> outRealUpperBand;
    QVector<double> outRealMiddleBand;
    QVector<double> outRealLowerBand;
    int outBegIdx= 0;
    int outNbElement = 0;

    // dynamically allocate output arrays
    // 5, 2.0, 2.0, TA_MAType_SMA - are defaults for BBANDS
    int sz = data_size - TA_BBANDS_Lookback(5, 2.0, 2.0, TA_MAType_SMA);

    Q_ASSERT(sz != 0);

    outRealUpperBand.resize(sz);
    outRealMiddleBand.resize(sz);
    outRealLowerBand.resize(sz);

    // get TA results
    TA_RetCode res = TA_BBANDS(0, data_size-1, data, 5, 2.0, 2.0, TA_MAType_SMA, &outBegIdx, &outNbElement,
                               outRealUpperBand.data(), outRealMiddleBand.data(), outRealLowerBand.data());
    if (res != TA_SUCCESS) {
        qDebug() << "Error: " << res;
        return -1;
    }
    else {
        for (int i = 0; i < outNbElement; i++)
            qDebug() << "Result for day #" << outBegIdx+i << ": outRealUpperBand: " << outRealUpperBand[i]
                        << " outRealMiddleBand: " << outRealMiddleBand[i]
                           << "outRealLowerBand: " << outRealLowerBand[i];
    }

    return TA_Shutdown();
}
