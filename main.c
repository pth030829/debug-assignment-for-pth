#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define ITER 10000000;


int main() {
    double awgn();
    /*
     Init Var
     E: Signal Energy
     SNR: Signal to Noise Ratio
     temp: Uniform random variable of noise over (0,1)
     sigma: Standard deviation of noise
     r0, r1: Correlator output
     error: Error counter
     poe: Probability of error estimate
     dsource: Binary data source
     */
    double E, SNR, temp, sigma, r0, r1, decis, error, poe, dsource;

    FILE *fp;
    time_t t;
    srand((unsigned)time(&t));

    E = 1.0; // Energy is normalized to unity (1)

    if ((fp = fopen("./data.txt", "w")) == NULL) {
        printf("File %s can't be treated as \"%s\"\n", "./data.txt", "w");
        exit(0);
    }
    fprintf(fp, "# Iterator = %d\n", ITER);
    fclose(fp);

    for (int SNRdB = 1; SNRdB < 16; SNRdB++) {
        SNR = pow(10.0, SNRdB/ 10.0);
        sigma = E / sqrt(2.0 * SNR); // Standard deviation of noise
        error = 0;

        // Gen of the binary data source
        for (int k = 0; k < ITER; k++) {
            temp = (double) rand() / RAND_MAX;

            if (temp < 0.5) { dsource = 0; }
            else { dsource = 1.0; }

            // Detection and probability of error calc
            // Adding AWGN noise
            if (dsource == 0) { // If the source data is 0
                r0 = E + awgn(sigma);
                r1 = awgn(sigma);
            } else { // Else the source data is 1
                r0 = awgn(sigma);
                r1 = E + awgn(sigma);
            }

            // Detector output
            if (r0 > r1) { decis = 0; }
            else { decis = 1.0; }

            // Error Check
            if (decis != dsource) { error++; }
        }

        // Probability of Error
        poe = error / ITER;

        printf("SNRdB = %d, BER = %.10lf\n", SNRdB, poe);
        fp = fopen("./data.txt", "a");
        fprintf(fp, "%d %.10lf\n", SNRdB, poe);
        fclose(fp);
    }
    return 0;
}

// AWGN noise gen
double awgn(double s) {
    double w, x1, x2, theta, noise;

    do { x1 = (double)rand() / RAND_MAX; } while (x1 == 1.0);
    x2 = (double)rand() / RAND_MAX;

    w = s * sqrt(-2.0 * log(1.0 - x1));
    theta = 2.0 * M_PI * x2;
    noise = w * cos(theta);

    return noise;
}

호민씨가 내주는 과제 입니다.
어찌하나 잘 봅시다!

이건 테스트 코드 입니다.

본 커멘트로 인해 실제로 동작하지 않습니다.

어떤 것을 추가 할껀가요?
박태현 연습

