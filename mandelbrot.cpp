#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mandelbrot.hpp" 

mandelbrot_t* initMandelbrotGen(unsigned int W, unsigned int H) {
    mandelbrot_t *newObj = (mandelbrot_t*) calloc(1, sizeof(mandelbrot_t));

    newObj->W = W;
    newObj->H = H;
    newObj->dx = (float)1 / W;
    newObj->dy = (float)1 / H;

    newObj->ROI_X = -1.325f, newObj->ROI_Y = 0;
    newObj->scale = 1;
    newObj->r2Max = 100.f;
    newObj->nMax  = 256;

    newObj->data = (unsigned char*) calloc(H*W*4, sizeof(unsigned char));

    return newObj;
}

void deleteMandelbrotObj(mandelbrot_t *obj) {
    free(obj->data);
    obj->data = nullptr;

    free(obj);
}

void calcMandelbrotSet(mandelbrot_t *obj) {
    for (int iy = 0; iy < obj->H; ++iy) {
        float x0 = ( (   - (float)obj->W / 2) * obj->dx + obj->ROI_X) * obj->scale, //??
              y0 = ( (iy - (float)obj->H / 2) * obj->dy + obj->ROI_Y) * obj->scale;
        
        for (int ix = 0; ix < obj->W; ++ix, x0 += obj->dx) {
            float X = x0, Y = y0;

            int curIter = 0;
            for (; curIter < obj->nMax; curIter++) {
                float x2 = X*X,
                      y2 = Y*Y,
                      xy = X*Y;
                float r2 = x2 + y2;
                    
                if (r2 >= obj->r2Max) {
                    break;
                }
                    
                X = x2 - y2 + x0,
                Y = xy + xy + y0;
            }
            if (curIter < obj->nMax) {
                unsigned char color = sqrtf(curIter / (float)obj->nMax) * 255;

                obj->data[(iy*obj->W + ix) * 4 + 0] = 255 - color;
                obj->data[(iy*obj->W + ix) * 4 + 1] = color % 2 * 64;
                obj->data[(iy*obj->W + ix) * 4 + 2] = color;
                obj->data[(iy*obj->W + ix) * 4 + 3] = 255;
            }
            else {
                obj->data[(iy*obj->W + ix) * 4 + 3] = 0;
            }
        }
    }
}