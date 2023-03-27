// SPDX-FileCopyrightText: 2023 Kota Meiwa
// SPDX-License-Identifier: MIT
 
#pragma once
#ifndef NEOPIXELPERFORMER_H
#define NEOPIXELPERFORMER_H
#include <Arduino.h>

typedef unsigned long ulong;

template <class NeoPixel>
class CNeoPixelPerformer
{
private:
    NeoPixel* m_neopixel;

protected:

public:
    CNeoPixelPerformer(NeoPixel* neopixel)
    :   m_neopixel(neopixel)
    {}
    ~CNeoPixelPerformer(){}
    
public:
    ///////////////////////
    inline void blink(ulong interval, uint32_t color_front, uint32_t color_back = 0){
        m_neopixel->fill(color_front), m_neopixel->show(), delay(interval);
        m_neopixel->fill(color_back), m_neopixel->show(), delay(interval);
    }

    ///////////////////////
    inline void transition_2colors(ulong duration, uint32_t rgb0, uint32_t rgb1, bool reverse=false){
        uint8_t* pt0 = reverse? (uint8_t*)&rgb1: (uint8_t*)&rgb0;
        uint8_t* pt1 = reverse? (uint8_t*)&rgb0: (uint8_t*)&rgb1;

        uint32_t color = *(uint32_t*)pt0;
        uint8_t* colorpt = (uint8_t*)&color;

        const int step_num = 16;
        for(int i=0; i<step_num; i++){
            for(int k=0; k<sizeof(color); k++){
                colorpt[k] += (int8_t(pt1[k]) - int8_t(pt0[k]))/step_num;
            }

            m_neopixel->fill(color), m_neopixel->show();
            delay(duration/step_num);
        }
    }

    ///////////////////////
    inline void moving_block(ulong duration, uint16_t width, uint32_t color_front, uint32_t color_back=0, bool reverse=false){
        for(int i=0, cnt=m_neopixel->numPixels()-width+1; i<cnt; i++){
            m_neopixel->fill(color_back);
            if(reverse){
                m_neopixel->fill(color_front, m_neopixel->numPixels()-width - i, width);
            }
            else{
                m_neopixel->fill(color_front, i, width);
            }
            m_neopixel->show();
            delay(duration/cnt);
        }
    }

    ///////////////////////
    inline void water_flow(ulong duration, uint32_t color_front, uint32_t color_back=0, bool reverse=false){
        int cnt = m_neopixel->numPixels()+1;
        ulong step = duration / cnt;

        m_neopixel->fill(reverse? color_front: color_back);
        m_neopixel->show(), delay(step);
        
        for(int i=1; i<cnt; i++){
            m_neopixel->fill(color_back);
            if(reverse){
                m_neopixel->fill(color_front, 0, cnt-i);
            }
            else{
                m_neopixel->fill(color_front, 0, i);
            }
            m_neopixel->show(), delay(step);
        }
    }
};


#endif  //NEOPIXELPERFORMER_H
