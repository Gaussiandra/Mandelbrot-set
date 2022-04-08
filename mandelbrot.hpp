#ifdef SSE
    #include <immintrin.h>

    const __m256 _255    = _mm256_set1_ps(255);
    const __m256 _range7 = _mm256_set_ps(7, 6, 5, 4, 3, 2, 1, 0);
#endif

struct mandelbrot_t {
    float ROI_X  = -1.325f, ROI_Y = 0;
    float scale  = 1;
    float dx     = 0, dy = 0;
    int nMaxInt  = 256;
    unsigned int W = 0, H = 0;

    #ifdef SSE
        __m256 nMax  = _mm256_set1_ps(nMaxInt);
        __m256 r2Max = _mm256_set1_ps(100);
    #else
        float r2Max = 100;
    #endif

    unsigned char *data;
};

void deleteMandelbrotObj(mandelbrot_t *obj);
mandelbrot_t* initMandelbrotGen(unsigned int W, unsigned int H);
void calcMandelbrotSet(mandelbrot_t *obj);