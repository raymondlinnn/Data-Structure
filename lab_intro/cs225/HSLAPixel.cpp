/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225{
    
    // First constructor
    HSLAPixel::HSLAPixel(){
        h = 0;
        s = 0;
        a = 1.0;
        l = 1.0;
    }
    
    // Second
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
        if(hue >= 0 && hue < 360){
            h = hue;
        }
        else{h = 0;}
        
        if(saturation >= 0 && saturation <= 1){
            s = saturation;
        }
        else if(saturation < 0){
            s = 0;
        }
        else{s = 1;}
        
        if(luminance >= 0 && luminance <=1) {
            l= luminance;
    }
        else if(luminance <0){
            l = 0;
        }
        else {l = 1;}
        
        a = 1;
    }
        //Third
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
        if(hue >= 0 && hue < 360){
            h = hue;}
        else{h = 0;}
        
        if(saturation >= 0 && saturation <= 1){
            s = saturation;
        }
        else if(saturation < 0){
            s = 0;
        }
        else{s = 1;}
        
        if(luminance >= 0 && luminance <=1) {
            l= luminance;
        }
        else if(luminance <0){
            l = 0;
        }
        else {l = 1;}
        
        if(alpha >= 0 && alpha <=1) {
            a= alpha;
        }
        else if(alpha <0){
            a = 0;
        }
        else {a = 1;}
    }
    
    
}
