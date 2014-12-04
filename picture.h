#pragma once
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include <icrsint.h>
#include<iomanip>
#include<vector>
#include<math.h>
using namespace std;
#import "C:\\program files\\common files\\system\\ado\\msado15.dll"  no_namespace rename("EOF", "adoEOF")
#define UNIT_LONG 0.000029
#define UNIT_LAT 0.000023
#define COLOR1  188*256*256+31*256+102
#define COLOR2  217*256*256+25*256+102 
#define COLOR3  237*256*256+28*256+36 
#define COLOR4  238*256*256+72*256+34 
#define COLOR5  254*256*256+120*256+8
#define COLOR6  245*256*256+158*256+29
#define COLOR7  255*256*256+217*256+1
#define COLOR8  255*256*256+242*256  
#define COLOR9  231*256*256+255*256+5
#define COLOR10  194*256*256+255*256+3
#define COLOR11  104*256*256+253*256+23
#define COLOR12  7*256*256+203*256+17
#define COLOR13  151*256+58
#define COLOR14  145*256+124
#define COLOR15  145*256+200
#define COLOR16  101*256+171
#define COLOR17  72*256+144

#define ECOLOR1 201*256*256+215*256+27
#define ECOLOR2 230*256*256+89*256+28
#define ECOLOR3 7*256*256+129*256+130 
#define ECOLOR4 246*256*256+189*256+23
#define ECOLOR5 202*256*256+22*256+67
#define ECOLOR6 97*256*256+50*256+136
class picture
{
public:
	picture(void);
	~picture(void);
	void makeMif();
};

