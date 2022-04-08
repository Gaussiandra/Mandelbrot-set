#include <cstdlib>
#include <cstdio>
#include "mandelbrot.hpp" 

mandelbrot_t* initMandelbrotGen(unsigned int W, unsigned int H) {
    mandelbrot_t *newObj = (mandelbrot_t*) aligned_alloc(32, 1*sizeof(mandelbrot_t));

    newObj->W  = W;
    newObj->H  = H;
    newObj->dx = (float)1 / W;
    newObj->dy = (float)1 / H;

    newObj->ROI_X   = -1.325f, newObj->ROI_Y = 0;
    newObj->scale   = 1;
    newObj->nMaxInt = 256;
    newObj->nMax    = _mm256_set1_ps((float)newObj->nMaxInt);
    newObj->r2Max   = _mm256_set1_ps((float)100);

    newObj->data = (unsigned char*) aligned_alloc(32, H*W*4*sizeof(unsigned char));

    return newObj;
}

void deleteMandelbrotObj(mandelbrot_t *obj) {
    free(obj->data);
    obj->data = nullptr;

    free(obj);
}

// переменные
void calcMandelbrotSet(mandelbrot_t *obj) {
    for (int iy = 0; iy < obj->H; ++iy) {
        for (int ix = 0; ix < obj->W; ix += 8) {
            float x0 = (((float)ix - (float)obj->W / 2) * obj->dx) * obj->scale + obj->ROI_X;
            float y0 = (((float)iy - (float)obj->H / 2) * obj->dy) * obj->scale + obj->ROI_Y;

            __m256 X0 = _mm256_add_ps(_mm256_set1_ps(x0), 
                                      _mm256_mul_ps(_range7, _mm256_set1_ps(obj->dx)));
            __m256 Y0 = _mm256_set1_ps(y0);
            __m256 X = X0, Y = Y0;

            __m256i nEachIter = _mm256_setzero_si256();
            for (int curIter = 0; curIter < obj->nMaxInt; curIter++) {
                __m256 x2 = _mm256_mul_ps(X, X),
                       y2 = _mm256_mul_ps(Y, Y),
                       xy = _mm256_mul_ps(X, Y),
                       r2 = _mm256_add_ps(x2, y2);
                
                __m256 cmp = _mm256_cmp_ps(r2, obj->r2Max, _CMP_LE_OQ); // os?
                int mask   = _mm256_movemask_ps(cmp);
                if (mask == 0) {
                    break;
                }
                nEachIter = _mm256_sub_epi32(nEachIter, _mm256_castps_si256(cmp)); //??
                    
                X = _mm256_add_ps(_mm256_sub_ps(x2, y2), X0);
                Y = _mm256_add_ps(_mm256_add_ps(xy, xy), Y0);
            }
            __m256 normalizedColors = _mm256_div_ps(_mm256_cvtepi32_ps(nEachIter), obj->nMax);
            __m256 colors = _mm256_mul_ps(_mm256_sqrt_ps(normalizedColors), _255);

            for (int i = 0; i < 8; ++i) {
                float *colorsFloat = (float*) &colors;
                int *itersInt = (int*) &nEachIter;

                //func
                if (itersInt[i] < obj->nMaxInt) {
                    obj->data[(iy*obj->W + ix + i) * 4 + 0] = 255 - colorsFloat[i];
                    obj->data[(iy*obj->W + ix + i) * 4 + 1] = (int)colorsFloat[i] % 2 * 64;
                    obj->data[(iy*obj->W + ix + i) * 4 + 2] = colorsFloat[i];
                    obj->data[(iy*obj->W + ix + i) * 4 + 3] = 255;
                }
                else {
                    obj->data[(iy*obj->W + ix + i) * 4 + 3] = 0;
                }
            }
        }
    }
}