/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*  -*- C++ -*-
*  Copyright (C) 1998 <developer@mozilla.org>
*
*
*  Permission is hereby granted, free of charge, to any person obtaining
*  a copy of this software and associated documentation files (the
*  "Software"), to deal in the Software without restriction, including
*  without limitation the rights to use, copy, modify, merge, publish,
*  distribute, sublicense, and/or sell copies of the Software, and to
*  permit persons to whom the Software is furnished to do so, subject to
*  the following conditions:
*
*  The above copyright notice and this permission notice shall be included 
*  in all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
*  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
*  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
*  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "nsSBCharSetProber.h"
/****************************************************************
255: Control characters that usually does not exist in any text
254: Carriage/Return
253: symbol (punctuation) that does not belong to word
252: 0 - 9

*****************************************************************/

namespace kencodingprober {
//Character Mapping Table:
const unsigned char Latin7_CharToOrderMap[] =
{
255,255,255,255,255,255,255,255,255,255,254,255,255,254,255,255,  //00
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  //10
+253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,  //20
252,252,252,252,252,252,252,252,252,252,253,253,253,253,253,253,  //30
253, 82,100,104, 94, 98,101,116,102,111,187,117, 92, 88,113, 85,  //40
 79,118,105, 83, 67,114,119, 95, 99,109,188,253,253,253,253,253,  //50
253, 72, 70, 80, 81, 60, 96, 93, 89, 68,120, 97, 77, 86, 69, 55,  //60
 78,115, 65, 66, 58, 76,106,103, 87,107,112,253,253,253,253,253,  //70
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  //80
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  //90
+253,233, 90,253,253,253,253,253,253,253,253,253,253, 74,253,253,  //a0
253,253,253,253,247,248, 61, 36, 46, 71, 73,253, 54,253,108,123,  //b0
110, 31, 51, 43, 41, 34, 91, 40, 52, 47, 44, 53, 38, 49, 59, 39,  //c0
 35, 48,250, 37, 33, 45, 56, 50, 84, 57,120,121, 17, 18, 22, 15,  //d0
124,  1, 29, 20, 21,  3, 32, 13, 25,  5, 11, 16, 10,  6, 30,  4,  //e0
  9,  8, 14,  7,  2, 12, 28, 23, 42, 24, 64, 75, 19, 26, 27,253,  //f0
};



const unsigned char win1253_CharToOrderMap[] =
{
255,255,255,255,255,255,255,255,255,255,254,255,255,254,255,255,  //00
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  //10
+253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,253,  //20
252,252,252,252,252,252,252,252,252,252,253,253,253,253,253,253,  //30
253, 82,100,104, 94, 98,101,116,102,111,187,117, 92, 88,113, 85,  //40
 79,118,105, 83, 67,114,119, 95, 99,109,188,253,253,253,253,253,  //50
253, 72, 70, 80, 81, 60, 96, 93, 89, 68,120, 97, 77, 86, 69, 55,  //60
 78,115, 65, 66, 58, 76,106,103, 87,107,112,253,253,253,253,253,  //70
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  //80
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  //90
+253,233, 61,253,253,253,253,253,253,253,253,253,253, 74,253,253,  //a0
253,253,253,253,247,253,253, 36, 46, 71, 73,253, 54,253,108,123,  //b0
110, 31, 51, 43, 41, 34, 91, 40, 52, 47, 44, 53, 38, 49, 59, 39,  //c0
 35, 48,250, 37, 33, 45, 56, 50, 84, 57,120,121, 17, 18, 22, 15,  //d0
124,  1, 29, 20, 21,  3, 32, 13, 25,  5, 11, 16, 10,  6, 30,  4,  //e0
  9,  8, 14,  7,  2, 12, 28, 23, 42, 24, 64, 75, 19, 26, 27,253,  //f0
};

//Model Table: 
//total sequences: 100%
//first 512 sequences: 98.2851%
//first 1024 sequences:1.7001%
//rest  sequences:     0.0359%
//negative sequences:  0.0148% 
const char GreekLangModel[] = 
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,3,2,2,3,3,3,3,3,3,3,3,1,3,3,3,0,2,2,3,3,0,3,0,3,2,0,3,3,3,0,
3,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,0,3,3,0,3,2,3,3,0,3,2,3,3,3,0,0,3,0,3,0,3,3,2,0,0,0,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,
0,2,3,2,2,3,3,3,3,3,3,3,3,0,3,3,3,3,0,2,3,3,0,3,3,3,3,2,3,3,3,0,
2,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,0,2,1,3,3,3,3,2,3,3,2,3,3,2,0,
0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,0,3,3,3,3,3,3,0,3,3,0,3,3,3,3,3,3,3,3,3,3,0,3,2,3,3,0,
2,0,1,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,2,3,0,0,0,0,3,3,0,3,1,3,3,3,0,3,3,0,3,3,3,3,0,0,0,0,
2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,0,3,0,3,3,3,3,3,0,3,2,2,2,3,0,2,3,3,3,3,3,2,3,3,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,3,2,2,2,3,3,3,3,0,3,1,3,3,3,3,2,3,3,3,3,3,3,3,2,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,2,0,3,0,0,0,3,3,2,3,3,3,3,3,0,0,3,2,3,0,2,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,0,3,3,3,3,0,0,3,3,0,2,3,0,3,0,3,3,3,0,0,3,0,3,0,2,2,3,3,0,0,
0,0,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,2,0,3,2,3,3,3,3,0,3,3,3,3,3,0,3,3,2,3,2,3,3,2,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,2,3,2,3,3,3,3,3,3,0,2,3,2,3,2,2,2,3,2,3,3,2,3,0,2,2,2,3,0,
2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,3,0,0,0,3,3,3,2,3,3,0,0,3,0,3,0,0,0,3,2,0,3,0,3,0,0,2,0,2,0,
0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,0,3,3,3,3,3,3,0,3,3,0,3,0,0,0,3,3,0,3,3,3,0,0,1,2,3,0,
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,2,0,0,3,2,2,3,3,0,3,3,3,3,3,2,1,3,0,3,2,3,3,2,1,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,3,3,0,2,3,3,3,3,3,3,0,0,3,0,3,0,0,0,3,3,0,3,2,3,0,0,3,3,3,0,
3,0,0,0,2,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,0,3,3,3,3,3,3,0,0,3,0,3,0,0,0,3,2,0,3,2,3,0,0,3,2,3,0,
2,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,3,1,2,2,3,3,3,3,3,3,0,2,3,0,3,0,0,0,3,3,0,3,0,2,0,0,2,3,1,0,
2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,0,3,3,3,3,0,3,0,3,3,2,3,0,3,3,3,3,3,3,0,3,3,3,0,2,3,0,0,3,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,0,3,3,3,0,0,3,0,0,0,3,3,0,3,0,2,3,3,0,0,3,0,3,0,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,3,0,0,0,3,3,3,3,3,3,0,0,3,0,2,0,0,0,3,3,0,3,0,3,0,0,2,0,2,0,
0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,3,0,3,0,2,0,3,2,0,3,2,3,2,3,0,0,3,2,3,2,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,3,0,0,2,3,3,3,3,3,0,0,0,3,0,2,1,0,0,3,2,2,2,0,3,0,0,2,2,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,0,3,3,3,2,0,3,0,3,0,3,3,0,2,1,2,3,3,0,0,3,0,3,0,3,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,3,3,3,0,3,3,3,3,3,3,0,2,3,0,3,0,0,0,2,1,0,2,2,3,0,0,2,2,2,0,
0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,3,0,0,2,3,3,3,2,3,0,0,1,3,0,2,0,0,0,0,3,0,1,0,2,0,0,1,1,1,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,3,1,0,3,0,0,0,3,2,0,3,2,3,3,3,0,0,3,0,3,2,2,2,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,0,3,3,3,0,0,3,0,0,0,0,2,0,2,3,3,2,2,2,2,3,0,2,0,2,2,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,3,3,3,2,0,0,0,0,0,0,2,3,0,2,0,2,3,2,0,0,3,0,3,0,3,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,3,2,3,3,2,2,3,0,2,0,3,0,0,0,2,0,0,0,0,1,2,0,2,0,2,0,
0,2,0,2,0,2,2,0,0,1,0,2,2,2,0,2,2,2,0,2,2,2,0,0,2,0,0,1,0,0,0,0,
0,2,0,3,3,2,0,0,0,0,0,0,1,3,0,2,0,2,2,2,0,0,2,0,3,0,0,2,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,3,0,2,3,2,0,2,2,0,2,0,2,2,0,2,0,2,2,2,0,0,0,0,0,0,2,3,0,0,0,2,
0,1,2,0,0,0,0,2,2,0,0,0,2,1,0,2,2,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0,
0,0,2,1,0,2,3,2,2,3,2,3,2,0,0,3,3,3,0,0,3,2,0,0,0,1,1,0,2,0,2,2,
0,2,0,2,0,2,2,0,0,2,0,2,2,2,0,2,2,2,2,0,0,2,0,0,0,2,0,1,0,0,0,0,
0,3,0,3,3,2,2,0,3,0,0,0,2,2,0,2,2,2,1,2,0,0,1,2,2,0,0,3,0,0,0,2,
0,1,2,0,0,0,1,2,0,0,0,0,0,0,0,2,2,0,1,0,0,2,0,0,0,2,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,3,3,2,2,0,0,0,2,0,2,3,3,0,2,0,0,0,0,0,0,2,2,2,0,2,2,0,2,0,2,
0,2,2,0,0,2,2,2,2,1,0,0,2,2,0,2,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,
0,2,0,3,2,3,0,0,0,3,0,0,2,2,0,2,0,2,2,2,0,0,2,0,0,0,0,0,0,0,0,2,
0,0,2,2,0,0,2,2,2,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,2,0,0,3,2,0,2,2,2,2,2,0,0,0,2,0,0,0,0,2,0,1,0,0,2,0,1,0,0,0,
0,2,2,2,0,2,2,0,1,2,0,2,2,2,0,2,2,2,2,1,2,2,0,0,2,0,0,0,0,0,0,0,
0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
0,2,0,2,0,2,2,0,0,0,0,1,2,1,0,0,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,3,2,3,0,0,2,0,0,0,2,2,0,2,0,0,0,1,0,0,2,0,2,0,2,2,0,0,0,0,
0,0,2,0,0,0,0,2,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,
0,2,2,3,2,2,0,0,0,0,0,0,1,3,0,2,0,2,2,0,0,0,1,0,2,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,0,2,0,3,2,0,2,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
0,0,2,0,0,0,0,1,1,0,0,2,1,2,0,2,2,0,1,0,0,1,0,0,0,2,0,0,0,0,0,0,
0,3,0,2,2,2,0,0,2,0,0,0,2,0,0,0,2,3,0,2,0,0,0,0,0,0,2,2,0,0,0,2,
0,1,2,0,0,0,1,2,2,1,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,1,2,0,2,2,0,2,0,0,2,0,0,0,0,1,2,1,0,2,1,0,0,0,0,0,0,0,0,0,0,
0,0,2,0,0,0,3,1,2,2,0,2,0,0,0,0,2,0,0,0,2,0,0,3,0,0,0,0,2,2,2,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,1,0,2,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,2,
0,2,2,0,0,2,2,2,2,2,0,1,2,0,0,0,2,2,0,1,0,2,0,0,2,2,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,0,0,0,3,0,0,2,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,2,
0,1,2,0,0,0,0,2,2,1,0,1,0,1,0,2,2,2,1,0,0,0,0,0,0,1,0,0,0,0,0,0,
0,2,0,1,2,0,0,0,0,0,0,0,0,0,0,2,0,0,2,2,0,0,0,0,1,0,0,0,0,0,0,2,
0,2,2,0,0,0,0,2,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,
0,2,2,2,2,0,0,0,3,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,1,
0,0,2,0,0,0,0,1,2,0,0,0,0,0,0,2,2,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,
0,2,0,2,2,2,0,0,2,0,0,0,0,0,0,0,2,2,2,0,0,0,2,0,0,0,0,0,0,0,0,2,
0,0,1,0,0,0,0,2,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
0,3,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,2,
0,0,2,0,0,0,0,2,2,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,0,2,2,1,0,0,0,0,0,0,2,0,0,2,0,2,2,2,0,0,0,0,0,0,2,0,0,0,0,2,
0,0,2,0,0,2,0,2,2,0,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,
0,0,3,0,0,0,2,2,0,2,2,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,
0,2,2,2,2,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
0,2,0,0,0,2,0,0,0,0,0,1,0,0,0,0,2,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,2,0,0,0,
0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,2,0,2,0,0,0,
0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,2,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

SequenceModel Latin7Model = 
{
  Latin7_CharToOrderMap,
  GreekLangModel,
  (float)0.982851,
  false,
  "ISO-8859-7"
};

SequenceModel Win1253Model = 
{
  win1253_CharToOrderMap,
  GreekLangModel,
  (float)0.982851,
  false,
  "windows-1253"
};
}


