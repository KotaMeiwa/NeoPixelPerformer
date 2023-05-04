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

    ///////////////////////
    inline void center2edge(ulong duration, uint32_t color_front, uint32_t color_back=0, bool reverse=false){
        bool center_2led = m_neopixel->numPixels()%2==0;
        int cnt = m_neopixel->numPixels()/2 + (!center_2led? 1: 0);
        ulong step = duration / (cnt+1);

        m_neopixel->fill(!reverse? color_back: color_front);
        m_neopixel->show(), delay(step);

        uint16_t center = m_neopixel->numPixels()/2 - (center_2led? 1: 0);
        
        if(!reverse){
            for(int i=0; i<cnt; i++){
                m_neopixel->fill(color_front, center - i, 2*i + (center_2led? 2: 1));
                m_neopixel->show(), delay(step);
            }
        }
        else{
            for(int i=0; i<cnt; i++){
                m_neopixel->fill(color_back, 0, i + 1);
                m_neopixel->fill(color_back, m_neopixel->numPixels()-1-i, i+1);
                m_neopixel->show(), delay(step);
            }
        }
    }

    ///////////////////////
    inline void fountain(ulong duration, uint16_t width, uint16_t gap, uint32_t color_front, uint32_t color_back=0, bool reverse=false){

        //LED数偶数なら中心はLED 2つ。
        uint16_t start_r = m_neopixel->numPixels()/2;
        uint16_t start_l = start_r + (m_neopixel->numPixels()%2==0? -1: 0);

        uint16_t total = width + gap;
        
        //関数繰り返しでも連続感があるように調整
        int cnt = m_neopixel->numPixels() - start_r;
        if(cnt%total)
            cnt -= cnt%total;
        
        ulong step = duration / cnt;

        for(int i=(!reverse? 0: cnt-1); !reverse? i<cnt: 0<=i; i+=(!reverse? 1: -1)){
            m_neopixel->fill(color_back);

            for(int led_l=start_l, led_r=start_r; 0<=led_l; led_l--, led_r++){
                if((i + led_l)%total < width){
                    m_neopixel->setPixelColor(led_l, color_front);
                    m_neopixel->setPixelColor(led_r, color_front);
                }
            }

            m_neopixel->show(), delay(step);
        }
    }
};


#endif  //NEOPIXELPERFORMER_H
