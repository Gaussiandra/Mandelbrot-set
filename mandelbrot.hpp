struct mandelbrot_t {
    float ROI_X = -1.325f, ROI_Y = 0;
    float scale = 1;
    float r2Max = 100.f;
    float dx    = 0, dy = 0;
    int   nMax  = 256;

    unsigned int W = 0, H = 0;
    unsigned char *data = nullptr;
};

void deleteMandelbrotObj(mandelbrot_t *obj);
mandelbrot_t* initMandelbrotGen(unsigned int W, unsigned int H);
void calcMandelbrotSet(mandelbrot_t *obj);