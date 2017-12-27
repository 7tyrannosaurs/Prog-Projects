#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void EnergiaVibrCO()
{
//* ��� ������������ ��������� ������� ��������� ��
//*
//* lCO - ������������ ������������� ������� �������� CO
//*
//* Ed_CO - ������� ����������� ��:
//* Ed_CO = 128434 K = 11,106 �� (Huber and Herzberg (1979))


//* ���� ��� ����� ������� � J (�� � meV),
//* �� ������ �������� ������� ������� �� ������� ww = 1.60219d-19 / 8065.47
//* ������ ������ hc

double o = 2169.81; // 1/cm Capitelli ESA STR-246 (2005) ! 2169.8 ! 1/cm Herzberg
double ox = 13.288; // 1/cm Capitelli ESA STR-246 (2005) ! 13.29 ! 1/cm Herzberg
double oy = 0.0105; // 1/cm Capitelli ESA STR-246 (2005) !

for (int i = 0; i < lCO+1; ++i)
    Eco[i] = hc*o*(i+0.5)-hc*ox*pow(i+0.5, 2)+hc*oy*pow(i+0.5, 3);
    // write(*,*) 'v=',v,'Eco(v)=',Eco(v)
}

void EnergiaVibrCO2()
{
//* ��� ������������ ��������� ������� ��������� ��2
//*
//* lCO2s - ��� ������������ ������������� ������� ������������� ������ ����������
//* lCO2b - ������������ ������������� ������� ������ ������
//* (��� ���������������� ���� ������ ��������������� ��� ���������� �����)
//* lCO2a - ������������ ������������� ������� �������������� ������ ����������
//*
//* Ed_CO2 - ������� ����������� CO2: Ed_CO2 = 64017 K = 5,5166 ��
//* Eco2 (0: lCO2s, 0: lCO2b, 0: lCO2a) - ��� ������ ������������� �������
//* iCO2 (0: lCO2s, 0: lCO2b, 0: lCO2a) - ��� ������, � ������� �� ��������
//* ���� ������� ������������ �������� ��2 � ��������������� ��������:
//* iCO2 (v1, v2, v3) = 0, ���� Eco2 (v1, v2, v3)> Ed_CO2
//* iCO2 (v1, v2, v3) = 1, ���� Eco2 (v1, v2, v3) <= Ed_CO2


//* ���� ��� ����� ������� � J (�� � meV),
//* �� ������ �������� ������� ������� �� ������� ww = 1.60219d-19 / 8065.47
//* ������ ������ hc

double o1 = 1345.04; // 1/cm Herzberg
double o2 = 667.25; // 1/cm Herzberg
double o3 = 2361.71; // 1/cm Herzberg
double ox11 = -3.63; // 1/cm Herzberg
double ox12 = 3.44; // 1/cm Herzberg
double ox13 = -19.288; // 1/cm Herzberg
double ox22 = -0.635; // 1/cm Herzberg
double ox23 = -12.51; // 1/cm Herzberg
double ox33 = -12.56; // 1/cm Herzberg
double oxll = 0.775; // 1/cm Herzberg

int d_1 = 1;
int d_2 = 2;
int d_3 = 1;

for (int k = 0; k < lCO2a+1; ++k)
    for (int j = 0; j < lCO2b+1; ++j)
        for (int i = 0; i < lCO2s+1; ++i)
        {
            Eco2[i][j][k] = hc*o1*(v1+d_1/2) +
            hc*o2*(v2+d_2/2) +
            hc*o3*(v3+d_3/2) +
            hc*ox11*(v1+d_1/2)*(v1+d_1/2) +
            hc*ox12*(v1+d_1/2)*(v2+d_2/2) +
            hc*ox13*(v1+d_1/2)*(v3+d_3/2) +
            hc*ox22*(v2+d_2/2)*(v2+d_2/2) +
            hc*ox23*(v2+d_2/2)*(v3+d_3/2) +
            hc*ox33*(v3+d_3/2)*(v3+d_3/2);

            if(Eco2[i][j][k] < Ed_CO2 || Eco2[i][j][k] == Ed_CO2)
                iCO2[i][j][k] = 1;
                // write(10,*) 'iCO2', iCO2[i][j][k]
                // write(10,*) 'Eco2(',v1,',',v2,',',v3,')=',Eco2[i][j][k]!
        }
 }

void CO2MixtureCoefficients_Rates()
{
//* ������������ ��� ������� ������� ���������� (P * tau)
//* ��������� ��������� (Achasov � ��., ��. ������ [5] � ������������ RatesCO2)

//*---
//* VT_2 : 'CO2(v1,v2,v3)+M<-->CO2(v1,v2-1,v3)+M'
//* CO2(0,1,0)+CO2<-->CO2(0,0,0)+CO2

ACO2_VT2_CO2[0] = -10.327;
ACO2_VT2_CO2[1] = 57.31;
ACO2_VT2_CO2[2] = -156.7;

//* CO2(0,1,0)+N2<-->CO2(0,0,0)+N2

ACO2_VT2_N2[0] = -11.018;
ACO2_VT2_N2[1] = 68.78;
ACO2_VT2_N2[2] = -188.5;

//* CO2(0,1,0)+CO<-->CO2(0,0,0)+CO

ACO2_VT2_CO[0] = -9.96;
ACO2_VT2_CO[1] = 51.65;
ACO2_VT2_CO[2] = -121.8;

//* CO2(0,1,0)+O2<-->CO2(0,0,0)+O2

ACO2_VT2_O2[0] = -10.634;
ACO2_VT2_O2[1] = 54.50;
ACO2_VT2_O2[2] = -116.8;

//* CO2(0,1,0)+O<-->CO2(0,0,0)+O

ACO2_VT2_O[0] = -11.011;
ACO2_VT2_O[1] = 49.40;
ACO2_VT2_O[2] = -77.3;

//*---
//* VV_(2-3) � VV_(1-2-3)
//* CO2(0,0,1)+CO2<-->CO2(0,3,0)+CO2 VV_(2-3)
//* CO2(0,0,1)+CO2<-->CO2(1,1,0)+CO2 VV_(1-2-3)

ACO2_VV23_CO2[0] = -12.662;
ACO2_VV23_CO2[1] = 88.87;
ACO2_VV23_CO2[2] = -272.5;

//* CO2(0,0,1)+N2<-->CO2(0,3,0)+N2 VV_(2-3)
//* CO2(0,0,1)+N2<-->CO2(1,1,0)+N2 VV_(1-2-3)

ACO2_VV23_N2[0] = -13.567;
ACO2_VV23_N2[1] = 106.70;
ACO2_VV23_N2[2] = -325.9;

//* CO2(0,0,1)+CO<-->CO2(0,3,0)+CO VV_(2-3)
//* CO2(0,0,1)+CO<-->CO2(1,1,0)+CO VV_(1-2-3)

ACO2_VV23_CO[0] = -11.857;
ACO2_VV23_CO[1] = 84.23;
ACO2_VV23_CO[2] = -271.7;

//* CO2(0,0,1)+O2<-->CO2(0,3,0)+O2 VV_(2-3)
//* CO2(0,0,1)+O2<-->CO2(1,1,0)+O2 VV_(1-2-3)

ACO2_VV23_O2[0] = -14.697;
ACO2_VV23_O2[1] = 122.27;
ACO2_VV23_O2[2] = -384.0;

//* CO2(0,0,1)+O<-->CO2(0,3,0)+O VV_(2-3)
//* CO2(0,0,1)+O<-->CO2(1,1,0)+O VV_(1-2-3)

ACO2_VV23_O[0] = -13.044;
ACO2_VV23_O[1] = 122.27;
ACO2_VV23_O[2] = -384.0;

//*---
//* VV_(2-CO) � VV_(1-2-CO)
//* 'CO2(0,0,0)+CO(1)<-->CO2(0,3,0)+CO(0)' VV_(2-CO)
//* 'CO2(0,0,0)+CO(1)<-->CO2(1,1,0)+CO(0)' VV_(1-2-CO)

ACO2_VV2CO[0] = -10.708;
ACO2_VV2CO[1] = 69.94;
ACO2_VV2CO[2] = -203.3;

//*---
//* VV_(3-CO) : 'CO2(v1,v2,v3+1)+CO(v)<-->CO2(v1,v2,v3)+CO(v+1)'
//* 'CO2(0,0,1)+CO(0)<-->CO2(0,0,0)+CO(1)'

ACO2_VV3CO[0] = -9.144;
ACO2_VV3CO[1] = 31.91;
ACO2_VV3CO[2] = -103.5;
}

void RatesCO2(T)
{
/* ����� �������� �.�������� � �. ��������� [1-3]
* �� ������������� ��������,
* ��� ������������ ���� ����������� �.�������� [4,5]


* �������� ������������:
*
* [1] �.�.�������, �.�.���������,
* ���� ���������� �������� ������������������� ��������������� ������ CO2�,
* Chem. Phys. 321 (2006) 293-310
*
* [2] �.�.������� � �.�.���������,
* ������� ��������� ��������� ������������� �������� �
* ����������� � ����������� ����� �,
* � Rarefied Gas Dynamics, ��� ��������� �. ��. ������� � �. �. �������,
* AIP Conference Proceedings 585, ������������ ���������� ��������,
* Melville, NY, 2001, pp. 620-627
*
* [3] �.�.�������, �.�.���������, �.�.�������, �.�.���������,
* ���������� ������������� ������������� ������� ������ ����������� ���������
* ����� � ����������� ���������,
* �������������� ������ � ������������ �������������, �. 3, � 2, 2011, ���.205-224
*
* [4] �. �������, �.�.�������,
* ������� ��������� ��������� ������� ��2:
* �� ������ �� ���������� � ������������� ����������� �����,
* Chem.Phys.415 (2013) 269-281
*
* [5] �. �������, �.�.�������,
* �� ������ ������� � �������� ����� � �������� �
* ������������� ��������,
* Chem.Phys.428 (2014) 90-104
*
*
* [6] �.�. ������, �.�. �������,
* '��������� �������� ������ V-V ��� CO2-GDL',
�������� 16, �������� ������������������,
* �����, ��������, 1986 (�� �������)
*
* [7] �.�. Schwartz, Z.L. ��������, �.�. Herzfeid,
* J.Chem.Phys. 20 (1952) 1591.
*
* [8] P. Marrone � C. Treanor, Phys. �������� 6, 1215 (1963)
*
* [9] M.Capitelli, G.Colonna, D.Giordano, L.Marraffa,
* A.Casavola, P.Minelli, D.Pagano, L.D.Pietanza, F.Taccogna,
* '������� ���������� ������� ��������� � ����������������� ��������
* ������������������� ������� ��������� ����� �� 50 �� 50000 �',
* ESA STR-246, 2005:


* ������ �������� ������������:
*
* [10] ������� �., ��������� �., ������� �., ��������� �.
* �������������� ������������� ������ CO2 � ��������� �������� ���������
* ����� � ������� ����� ',
* AIP Conf Proc 2009, 1084, pp-831-836.
*
* [11] ������� �., ��������� �., ������� �., ��������� �.
* ���������� ��������� ������� ��� ������������� ������� CO2
* � ������� ���� ������ �������� ���� ',
* Shock Waves 2011; 21 (3): 273-87
*
* [12] �. �. �������, �. �. ��������� � �. �������,
* '�����������-���������� �������� � ������� ������ �� ����',
* �: ������������ ������ � ������ � ����������,
* ����������� ������
* Open Plasma Physics Journal, Vol.7, 2014, pp.76-87
*
* [13] �. �������� � �.�������,
* ����������� ����������� ������� �����: ��������� �����������-����������
* �������� � ������������� ",
* ��������� ����������� AIP 1628, 1245 (2014); doi: 10.1063 / 1.4902734
*
* [14] �. ����������, �. ������, �. ������, �. ��������,
* ������� ��������� ����� ��������� ������������ �������� CO2 + CO2�,
* Journ. ����. ����� 33 (2012) 1806-1819

****** ****** ****** ****** ****** *******
*
* ��� ������������ ��������� ������������ �������� ��������� ��������� �
* ��������� ������������ ���������:

* VT_2
* CO2 (v1.v2.v3) + CO2 <-> CO2 (v1.v2-1.v3) + CO2
* CO2 (v1.v2.v3) + CO <-> CO2 (v1.v2-1.v3) + CO
* CO2 (v1.v2.v3) + O2 <-> CO2 (v1.v2-1.v3) + O2
* CO2 (v1.v2.v3) + O <-> CO2 (v1.v2-1.v3) + O
* VV_ (2-3)
* CO2 (v1.v2 + 3.v3) + CO2 <-> CO2 (v1.v2.v3 + 1) + CO2
* VV_ (1-2-3)
* CO2 (v1 + 1.v2 + 1.v3) + CO2 <-> CO2 (v1.v2.v3 + 1) + CO2
* VV_ (1-2-CO)
* CO2 (v1 + 1.v2 + 1.v3) + CO (v) <-> CO2 (v1.v2.v3) + CO (v + 1)
* VV_ (2-CO)
* CO2 (v1.v2 + 3.v3) + CO (v) <-> CO2 (v1.v2.v3) + CO (v + 1)
* VV_ (3-CO)
* CO2 (v1.v2.v3) + CO (v) <-> CO2 (v1.v2.v3-1) + CO (v + 1)
* VV_ (1-2)
* CO2 (v1 + 1.v2.v3) + CO2 <-> CO2 (v1.v2 + 2.v3) + CO2
* ����������� / ������������
* CO2 (v1.v2.v3) + CO2 <-> CO (v) + O + CO2
* CO2 (v1.v2.v3) + CO <-> CO (v) + O + CO
*
* �������� �������� ����������� � ������� ��������� ��������� [1]:
* ������������ �������� ������������� �������������� ��������� �����
* ������ ������� �������������� ����������� ����������� � �������������� �����������������

������ [6],
* ��������� ������������ �������� (��� ����� ������� ���������) ����������� ��
* ������ ������ SSH [7], ���������������� ��� ������������ ������� [1].
* ������������ �������� �������� ��������� ������� �
* �������������� �������� ������ ���������
* ��������� ��������� �������. (��. ����� [4])
*
* ��� ������������ ����������� ��2 �� ����������
* ������ ��������-������� [8], ���������� ��� ����������� �������,
* ������������ � [2], [1] (��. ����� [5])
*
****** ****** ****** ****** ****** *******
*
* T - ����������� (K)*/

//*****
KTg = 0.087*T; // ! in meV (T e' in K)
//*****

//* ������� ������������� CO2: Zco2,
//* Zco2_U ��������� � ������� �������� ����������� [1],
//* U = Dco2 / 6,
//* Dco2 = 64017 K - ������� ����������� CO2 � ���������

if (iniCO2 == eq.1)
{
 double Zco2 = 0;
 double Zco2_U = 0;
 for (int i = 0; i < lCO2s+1; ++i)
    for (int j = 0; j < lCO2b+1; ++j)
        for (int k = 0; k < lCO2a+1; ++k)
        {
            Zco2 = Zco2 + (i2+1) * exp(-Eco2[i][j][k]/KTg) * iCO2[i][j][k]; // ����������, ����� Eco2 [i] [j] [k]> Ed_CO2
            Zco2_U = Zco2_U + (i2+1) * exp(-Eco2[i][j][k]/(0.087*(-10669.5))) * iCO2[i][j][k]; // ����������, ����� Eco2 [i] [j] [k]> Ed_CO2
        }
}

// *****
// * CO-�������: Zco

double Zco = 0;
for (int i = 0; i < NLCOl ++i)
    Zco = Zco+exp(-Eco[i]/KTg);

// *****
// * ������� ������������� ��������� CO2 [9]:
// c Zco2Rot = (1 / sigma) * ((k * T) / (h * c * B_0)) (��������� (48) ������ [9])

double Zco2Rot;
Zco2Rot = (1/2) * ((Kb*T)/(hPlank*clight*0.3915e2));

// *****
// * ������� ������������� ��������� CO [9]:

double ZcoRot;
ZcoRot = ((Kb*T)/(hPlank*clight*1.7149e2));

//*****
/* ** VT_2
* ����� ���������� (PtauCO2_VT2_CO2) �� Achasov et al. [6]
* (������ ���������, �������� ��� �������� � ������� ���
* ������� ����������, ������ �������� � ��. [6], �. �. ������� ��� p * tau)
* ������� ���������
* �� ������ ������������� �� atm * s � Pa * s
* 1atm = 1,01325e5 ��
* log_10 (P * tau) = sum (A_i * (T ^ -1 / 3) ^ i) */

double Tm1o3;
Tm1o3 = pow (T,-1/3);
double sum;

// * M = CO2
sum = ACO2_VT2_CO2[0] * pow(Tm1o3,0) + ACO2_VT2_CO2[1] * pow(Tm1o3,1) + ACO2_VT2_CO2[2] * pow(Tm1o3,2);
PtauCO2_VT2_CO2 = pow(10, sum); // atm*s
PtauCO2_VT2_CO2 = PtauCO2_VT2_CO2 * 1.01325e5; // Pa*s
// kCO2_VT2_CO2 = (Kb*T) / PtauCO2_VT2_CO2!! ! ! m3/s (k_(010->000)^(CO2))
kCO2_VT2_CO2 = (Kb*T) / PtauCO2_VT2_CO2 * 1.0e6; // cm3/s (k_(010->000)^(CO2))

//* M = CO
sum = ACO2_VT2_CO[0] * pow(Tm1o3,0) + ACO2_VT2_CO[1] * pow(Tm1o3,1) + ACO2_VT2_CO[2] * pow(Tm1o3,2);
PtauCO2_VT2_CO = pow(10, sum); // atm*s
PtauCO2_VT2_CO = PtauCO2_VT2_CO * 1.01325e5; // Pa*s
// kCO2_VT2_CO = (Kb*T) / PtauCO2_VT2_CO! ! ! ! m3/s (k_(010->000)^(CO))
kCO2_VT2_CO = (Kb*T) / PtauCO2_VT2_CO * 1.0e6; // cm3/s (k_(010->000)^(CO))

//* M = O2
sum = ACO2_VT2_O2[0] * pow(Tm1o3,0) + ACO2_VT2_O2[1] * pow(Tm1o3,1) + ACO2_VT2_O2[2] * pow(Tm1o3,2);
PtauCO2_VT2_O2 = pow(10, sum); // atm*s
PtauCO2_VT2_O2 = PtauCO2_VT2_O2 * 1.01325e5; // Pa*s
// kCO2_VT2_O2 = (Kb*T) / PtauCO2_VT2_O2! ! ! ! m3/s (k_(010->000)^(O2))
kCO2_VT2_O2 = (Kb*T) / PtauCO2_VT2_O2 * 1.0e6; // cm3/s (k_(010->000)^(O2))

//* M = O
sum = ACO2_VT2_O[0] * pow(Tm1o3,0) + ACO2_VT2_O[1] * pow(Tm1o3,1) + ACO2_VT2_O[2] * pow(Tm1o3,2);
PtauCO2_VT2_O = pow(10, sum); // atm*s
PtauCO2_VT2_O = PtauCO2_VT2_O * 1.01325e5; // Pa*s
// kCO2_VT2_O = (Kb*T) / PtauCO2_VT2_O!! ! ! m3/s (k_(010->000)^(O))
kCO2_VT2_O = (Kb*T) / PtauCO2_VT2_O * 1.0e6; // cm3/s (k_(010->000)^(O))

//*****

// ** VV_ (2-3) � VV_ (1-2-3) (�, ��� ���������, VV_ (1-2))
// * ����� ���������� (PtauCO2_VV23_CO2) Achasov et al. [6]
// * M = CO2

sum = 0;
sum = ACO2_VV23_CO2[0] * pow(Tm1o3,0) + ACO2_VV23_CO2[1] * pow(Tm1o3,1) + ACO2_VV23_CO2[2] * pow(Tm1o3,2);
PtauCO2_VV23_CO2 = pow(10, sum); // atm*s

// * �� ������ ������������� atm * s � Pa * s
// * 1atm = 1.01325e5 Pa

PtauCO2_VV23_CO2 = PtauCO2_VV23_CO2 * 1.01325e5; // Pa*s

// * ������ ���������: � ���� ������ ������ ���� �������� �������� (k_ (000-> 030) ^ (1-> 0) e k_ (000-> 110) ^ (1-> 0))
// * ��������� ����������� ������ ���� ��������� �����
// * ��������� ������� ������� (k_ (030-> 000) ^ (0-> 1) � k_ (110-> 000) ^ (0-> 1))
// c backk = (Kb * T) / PtauCO2_VV2CO! ! ! ! ! ! m3 / s (k_ (000-> 030) ^ (1-> 0) e k_ (000-> 110) ^ (1-> 0))

double backk;

backk = (Kb*T) / PtauCO2_VV23_CO2 * 1.0e6; // cm3/s (k_001->030)
kCO2_VV23_CO2 = backk*(1/4)* exp((Eco2[0][3][0]-Eco2[0][0][1])/KTg); // (k_(030->001)^(CO2))
kCO2_VV123_CO2 = backk*(1/2)* exp((Eco2[1][1][0]-Eco2[0][0][1])/KTg); // (k_(110->001)^(CO2))

/* ** VV_(1-2)
****************** ******************
****************** ******************
****************** ******************
****************** ******************
****************** ? ��������� ����������� ? ******************
****************** ******************
****************** ******************
****************** ******************

*��� �������� �� ������� � ����������������� ����������.
*����. ������� ���������� 10 ��� 100 ��� �������� �������� VV_ (1-2-3),
*������ ��� ����������� ����� �������� VV_ (1-2)
*������ ���������� ����� ���������� ���������� */

kCO2_VV12_CO2 = backk * 3 * exp((Eco2[1][1][0]-Eco2[0][2][0])/KTg) * 10; // ! * 100 ! (k_(100->020)^(CO2))

// *****
// ** VV_ (2-CO) � VV_ (1-2-CO)
// * ����� ���������� (PtauCO2_VV2CO) ������� � ��. [6]

sum = 0;
sum = ACO2_VV2CO[0] * pow(Tm1o3,0) + ACO2_VV2CO[1] * pow(Tm1o3,1) + ACO2_VV2CO[2] * pow(Tm1o3,2);
PtauCO2_VV2CO = pow(10, sum); // atm*s

// * �� ������ ������������� atm * s � Pa * s
// * 1atm = 1.01325e5 Pa

PtauCO2_VV2CO = PtauCO2_VV2CO * 1.01325e5; // Pa*s

// * ������ ���������: � ���� ������ ������ ���� �������� �������� (k_ (000-> 030) ^ (1-> 0) e k_ (000-> 110) ^ (1-> 0))
// * ��������� ����������� ������ ���� ��������� �����
// * ��������� ������� ������� (k_ (030-> 000) ^ (0-> 1) � k_ (110-> 000) ^ (0-> 1))
// c backk = (Kb * T) / PtauCO2_VV2CO! ! ! ! ! ! m3 / s (k_ (000-> 030) ^ (1-> 0) e k_ (000-> 110) ^ (1-> 0))

backk = (Kb*T) / PtauCO2_VV2CO * 1.0e6; // cm3/s (k_(000->030)^(1->0) e k_(000->110)^(1->0))
kCO2_VV2CO = backk*(1/4)*exp((Eco2[0][3][0]+Eco[0]-Eco2[0][0][0]-Eco[1])/KTg); // k_(030->000)^(0->1)
kCO2_VV12CO = backk*(1/2)* exp((Eco2[1][1][0]+Eco[0]-Eco2[0][0][0]-Eco[1])/KTg); // k_(110->000)^(0->1)

//*****
// ** VV_ (3-CO)
// * ����� ���������� (PtauCO2_VV3CO) ������� � ��. [6]

sum = 0;
sum = ACO2_VV3CO[0] * pow(Tm1o3,0) + ACO2_VV3CO[1] * pow(Tm1o3,1) + ACO2_VV3CO[2] * pow(Tm1o3,2);
PtauCO2_VV3CO = pow(10, sum); // atm*s

//* we have to convert atm*s to Pa*s
//* 1atm=1.01325e5 Pa

PtauCO2_VV3CO = PtauCO2_VV3CO * 1.01325e5; // Pa*s

// kCO2_VV3CO = (Kb*T) / PtauCO2_VV3CO!! ! ! m3/s k_(001->000)^(0-->1)

kCO2_VV3CO = (Kb*T) / PtauCO2_VV3CO * 1.0e6; // cm3/s k_(001->000)^(0-->1)

//****** ****** ****** ****** ****** ******

//****** ������ ������������� ******
//*****
//* VT_2 : CO2(v1,v2,v3)+M<-->CO2(v1,v2-1,v3)+M

//*--
//* CO2(v1,v2,v3)+CO2<-->CO2(v1,v2-1,v3)+CO2

double PPkf;
double PPkb;

for (int j = 1; j < lCO2b; ++j)
{
    PPkf = kCO2_VT2_CO2 * v2; // cm^3/(s*part)
    //* PPkf = PPkf * AvoNum*1e-6!! ! ! ! ! m3/(s*mol)
    for (int i = 0, i < lCO2s+1; ++i)
        for (int k = 0; k < lCO2a+1; ++k)
        {
            PPkb = PPkf * ((j+1)/j) * exp((Eco2[i][j-1][k]-Eco2[i][j][k])/KTg);
            R_VT2_CO2_f[i][j][k] = PPkf * iCO2[i][j][k];
            R_VT2_CO2_b[i][j][k] = PPkb * iCO2[i][j][k];
        }
}

//*--
//* CO2(v1,v2,v3)+CO<-->CO2(v1,v2-1,v3)+CO

for (int j = 1; j < lCO2b; ++j)
{
    PPkf = kCO2_VT2_CO * v2; // cm^3/(s*part)
    //* PPkf = PPkf * AvoNum*1e-6!! ! ! ! ! m3/(s*mol)
    for (int i = 0, i < lCO2s+1; ++i)
        for (int k = 0; k < lCO2a+1; ++k)
        {
            PPkb = PPkf * ((j+1)/j) * exp((Eco2[i][j-1][k]-Eco2[i][j][k])/KTg);
            R_VT2_CO_f[i][j][k] = PPkf * iCO2[i][j][k];
            R_VT2_CO_b[i][j][k] = PPkb * iCO2[i][j][k];
        }
}

//*--
//* CO2(v1,v2,v3)+O2<-->CO2(v1,v2-1,v3)+O2

for (int j = 1; j < lCO2b; ++j)
{
    PPkf = kCO2_VT2_O2 * v2; // cm^3/(s*part)
    //* PPkf = PPkf * AvoNum*1e-6!! ! ! ! ! m3/(s*mol)
    for (int i = 0, i < lCO2s+1; ++i)
        for (int k = 0; k < lCO2a+1; ++k)
        {
            PPkb = PPkf * ((j+1)/j) * exp((Eco2[i][j-1][k]-Eco2[i][j][k])/KTg);
            R_VT2_O2_f[i][j][k] = PPkf * iCO2[i][j][k];
            R_VT2_O2_b[i][j][k] = PPkb * iCO2[i][j][k];
        }
}

//*--
//* CO2(v1,v2,v3)+O<-->CO2(v1,v2-1,v3)+O

for (int j = 1; j < lCO2b; ++j)
{
    PPkf = kCO2_VT2_O * v2; // cm^3/(s*part)
    //* PPkf = PPkf * AvoNum*1e-6!! ! ! ! ! m3/(s*mol)
    for (int i = 0, i < lCO2s+1; ++i)
        for (int k = 0; k < lCO2a+1; ++k)
        {
            PPkb = PPkf * ((j+1)/j) * exp((Eco2[i][j-1][k]-Eco2[i][j][k])/KTg);
            R_VT2_O_f[i][j][k] = PPkf * iCO2[i][j][k];
            R_VT2_O_b[i][j][k] = PPkb * iCO2[i][j][k];
        }
}

//*****
//* VV_(2-3) : CO2(v1,v2+3,v3)+M<-->CO2(v1,v2,v3+1)+M
//*--
//* CO2(v1,v2+3,v3)+CO2<-->CO2(v1,v2,v3+1)+CO2

for (int k = 0; k < lCO2a; ++k)
{
    for (int j = 0; j < lCO2b-2; ++j)
    {
        PPkf = kCO2_VV23_CO2 * ((j+1)*(j+2)*(j+3)*(k+1)) / (3*2*1); // cm^3/(s*part)

        //* PPkf = PPkf * AvoNum*1e-6! ! ! ! ! ! ! m3/(s*mol)

        for (int i = 0; i < lCO2s+1; ++i)
        {
            PPkb = PPkf * ((j+3+1)/(j+1)) * exp((Eco2[i][j][k+1]-Eco2[i][j+3][k])/KTg);
            R_VV23_CO2_f[i][j+3][k] = PPkf * iCO2[i][j+3][k] * iCO2[i][j][k+1];
            R_VV23_CO2_b[i][j+3][k] = PPkb * iCO2[i][j+3][k] * iCO2[i][j][k+1];
        }
    }
}

//*****
//* VV_(1-2-3) : CO2(v1+1,v2+1,v3)+M<-->CO2(v1,v2,v3+1)+M
//*--
//* CO2(v1+1,v2+1,v3)+CO2<-->CO2(v1,v2,v3+1)+CO2

for (int k = 0; k < lCO2a; ++k)
{
    for (int j = 0; j < lCO2b; ++j)
    {
        for (int i = 0; i < lCO2s; ++i)
        {

            PPkf = kCO2_VV123_CO2 * ((j+1)*(j+2)*(j+3)*(k+1)); // cm^3/(s*part)

            //* PPkf = PPkf * AvoNum*1e-6! ! ! ! ! ! ! m3/(s*mol)

            PPkb = PPkf * ((j+1+1)/(j+1)) * exp((Eco2[i][j][k+1]-Eco2[i+1][j+1][k])/KTg);
            R_VV123_CO2_f[i+1][j+1][k] = PPkf * iCO2[i+1][j+1][k] * iCO2[i][j][k+1];
            R_VV123_CO2_b[i+1][j+1][k] = PPkb * iCO2[i+1][j+1][k] * iCO2[i][j][k+1];
        }
    }
}

//*****
//* VV_(1-2-CO) : CO2(v1+1,v2+1,v3)+CO(v)<-->CO2(v1,v2,v3)+CO(v+1)

for (int l = 0; l < lCO; ++l)
{
    for (int j = 0; j < lCO2b; ++j)
    {
        for (int i = 0; i < lCO2s; ++i)
        {

            PPkf = kCO2_VV12_CO * ((i+1)*(j+1)*(l+1)); // cm^3/(s*part)

            //* PPkf = PPkf * AvoNum*1e-6! ! ! ! ! ! ! m3/(s*mol)

            for (int k = 0; k < lCO2a+1; ++k)
            {
                PPkb = PPkf * ((j+1+1)/(j+1)) * exp((Eco2[i][j][k]+Eco[l+1]-Eco2[i+1][j+1][k]-Eco[l])/KTg);
                R_VV12CO_f[i+1][j+1][k][l] = PPkf * iCO2[i+1][j+1][k];
                R_VV12CO_b[i+1][j+1][k][l] = PPkb * iCO2[i+1][j+1][k];
            }
        }
    }
}

//*****
//* VV_(2-CO) : CO2(v1,v2+3,v3)+CO(v)<-->CO2(v1,v2,v3)+CO(v+1)

for (int l = 0; l < lCO; ++l)
{
    for (int j = 0; j < lCO2b-2; ++j)
    {
        PPkf = kCO2_VV2_CO * ((j+1)*(j+2)*(j+3)*(l+1))/(3*2*1); // cm^3/(s*part)

        //* PPkf = PPkf * AvoNum*1e-6! ! ! ! ! ! ! m3/(s*mol)

        for (int k = 0; k < lCO2a+1; ++k)
        {
            for (int i = 0; i < lCO2s+1; ++i)
            {
                PPkb = PPkf * ((j+3+1)/(j+1)) * exp((Eco2[i][j][k]+Eco[l+1]-Eco2[i][j+3][k]-Eco[l])/KTg);
                R_VV2CO_f[i][j+3][k][l] = PPkf * iCO2[i][j+3][k];
                R_VV2CO_b[i][j+3][k][l] = PPkb * iCO2[i][j+3][k];
            }
        }
    }
}

//*****
//* VV_(3-CO) : CO2(v1,v2,v3)+CO(v)<-->CO2(v1,v2,v3-1)+CO(v+1)

for (int l = 0; l < lCO; ++l)
{
    for (int k = 0; j < lCO2a; ++k)
    {
        PPkf = kCO2_VV3_CO * ((k)*(l+1)); // cm^3/(s*part)

        //* PPkf = PPkf * AvoNum*1e-6! ! ! ! ! ! ! m3/(s*mol)

        for (int j = 0; j < lCO2b+1; ++j)
        {
            for (int i = 0; i < lCO2s+1; ++i)
            {
                PPkb = PPkf * exp((Eco2[i][j][k-1]+Eco[l+1]-Eco2[i][j][k]-Eco[l])/KTg);
                R_VV3CO_f[i][j+3][k][l] = PPkf * iCO2[i][j][k];
                R_VV3CO_b[i][j+3][k][l] = PPkb * iCO2[i][j][k];
            }
        }
    }
}

//*****
//* VV_(1-2) : CO2(v1+1,v2,v3)+M<-->CO2(v1,v2+2,v3)+M
//*--
//* CO2(v1+1,v2,v3)+CO2<-->CO2(v1,v2+2,v3)+CO2

for (int k = 0; k < lCO2a+1; ++k)
{
    for (int j = 0; j < lCO2b-1; ++j)
    {
        for (int i = 0; i < lCO2s; ++i)
        {

            PPkf = kCO2_VV12_CO2 * ((i+1)*(j+1)*(j+2))/2; // (2.*1.)// cm^3/(s*part)

            //* PPkf = PPkf * AvoNum*1e-6! ! ! ! ! ! ! m3/(s*mol)

            PPkb = PPkf * ((j+1)/(j+2+1)) * exp((Eco2[i][j+2][k]-Eco2[i+1][j][k])/KTg);
            R_VV12_CO2_f[i+1][j][k] = PPkf * iCO2[i+1][j][k] * iCO2[i][j+2][k];
            R_VV12_CO2_b[i+1][j][k] = PPkb * iCO2[i+1][j][k] * iCO2[i][j+2][k];
        }
    }
}

//*****
// * CO2 diss / rec: CO2 (v1, v2, v3) + M <-> CO (v) + O + M
// * -
// * CO2 (v1, v2, v3) + CO2 <-> CO (v) + O + CO2
// * ����������� ����������� ��������� kf = PPkfeq �������� � [3] (������� 1)

double PPkfeq;
PPkfeq = 7.2e11 * pow(T, (1/2)) * exp(-36850/T); // cm3/(mol*s)
PPkfeq = PPkfeq/AvoNum; // cm3/(part*s)
double PPkf0;

for (int k = 0; k < lCO2a+1; ++k)
{
    for (int j = 0; j < lCO2b+1; ++j)
    {
        for (int i = 0; i < lCO2s+1; ++i)
        {
            // * ������� PPkf0 ��������� � [1]
������������// * (� ���� ������� U = Dco2 / 6 = 10669,5, Dco2 = 64017 K - ������� ����������� CO2)

            PPkf0 = Zco2/Zco2_U * exp((Eco2[i][j][k]/0.087)*(1/T+1/10669.5)) * PPkfeq;

            for (int l = 0; l < lCO+1; ++l)
            {
                PPkf = PPkf0 * exp(-Eco(l)/KTg) / Zco; // ������������
                PPkb = PPkf * pow((massaCO2/(massaCO*massaO)), (3/2)) * pow((2*pigrec*Kb*T), (-3/2)) * pow(hPlank,3) * (j+1) * Zco2Rot/ZcoRot * exp( - (Eco2[i][j][k] - Eco[l] -(3.95e5/AvoNum)*6.241506d21+(1.15e5/AvoNum)*6.241506d21-4.13643e-19*6.241506d21)/KTg;
                R_diss_CO2_f[i][j][k][l] = PPkf * iCO2[i][j][k]; // ����������� ��2
                R_rec_CO2_b[i][j][k][l] = PPkb * iCO2[i][j][k]; // ������������ ��2
            }
        }
    }
}

//*--
// * CO2 (v1, v2, v3) + CO <-> CO (v) + O + CO
// * ����������� ����������� ��������� kf = PPkfeq �������� � [3] (������� 1)

PPkfeq = 1.2e11 * T**(1./2.) * exp(-36850./T); // cm3/(mol*s)
PPkfeq = PPkfeq/AvoNum; // cm3/(part*s)

for (int k = 0; k < lCO2a+1; ++k)
{
    for (int j = 0; j < lCO2b+1; ++j)
    {
        for (int i = 0; i < lCO2s+1; ++i)
        {
            // * ������� PPkf0 ��������� � [1]
������������// * (� ���� ������� U = Dco2 / 6 = 10669,5, Dco2 = 64017 K - ������� ����������� CO2)

            PPkf0 = Zco2/Zco2_U * exp((Eco2[i][j][k]/0.087)*(1/T+1/10669.5)) * PPkfeq;

            for (int l = 0; l < lCO+1; ++l)
            {
                PPkf = PPkf0 * exp(-Eco(l)/KTg) / Zco; // ������������
                PPkb = PPkf * pow((massaCO2/(massaCO*massaO)), (3/2)) * pow((2*pigrec*Kb*T), (-3/2)) * pow(hPlank,3) * (j+1) * Zco2Rot/ZcoRot * exp( - (Eco2[i][j][k] - Eco[l] -(3.95e5/AvoNum)*6.241506d21+(1.15e5/AvoNum)*6.241506d21-4.13643e-19*6.241506d21)/KTg;
                R_diss_CO_f[i][j][k][l] = PPkf * iCO2[i][j][k]; // ����������� ��2
                R_rec_CO_b[i][j][k][l] = PPkb * iCO2[i][j][k]; // ������������ ��2
            }
        }
    }
}
}

void writing (double T)
{
    cout << "VT_2: CO2(v1.v2.v3)+CO2 --> CO2(v1.v2-1.v3)+CO2" << endl;
    cout << "T=" << T << endl;

    for (int k = 0; k < lCO+1; ++k)
    {
        for (int j = 0; j < lCO2b+1; ++j)
        {
            for (int i = 0; i < lCO2s+1; ++i)
            {
                cout <<  R_VT2_CO2_f[i][j][k];
            }
        }
    }

    cout << "VT_2: CO2(v1.v2.v3)+CO2 <-- CO2(v1.v2-1.v3)+CO2" << endl;
    cout << "T=" << T << endl;

    for (int k = 0; k < lCO+1; ++k)
    {
        for (int j = 0; j < lCO2b+1; ++j)
        {
            for (int i = 0; i < lCO2s+1; ++i)
            {
                cout <<  R_VT2_CO2_b[i][j][k];
            }
        }
    }
}

int main () {

int lCO = 67;
int lCO2s = 34;
int lCO2b = 67;
int lCO2a = 20;
int Ed_CO = 11106; // meV
double Ed_CO2 = 5516.6; // meV
// Kb (J/K), hPlank (J*s), clight (m/s)
double Kb = 1.380658d-23;
double hPlank = 6.62559d-34;
double clight = 299792458;
double AvoNum = 6.0225e23; // Avogadro number (mol-1))
double massaCO2 = 7.306e-26;
double massaCO = 28.01*1.6605402e-27;
double massaO = 2.6565e-26; // kg
int v, v1, v2, v3, w1, w2, w3;

double KTg;
double Keqco2;
double kCO2_VT2_CO2; // !! ! k_(010->000)^M ; VT_2
double kCO2_VT2_CO; // k_(010->000)^M ; VT_2
double kCO2_VT2_O2; // k_(010->000)^M ; VT_2
double kCO2_VT2_O; // k_(010->000)^M ; VT_2
double kCO2_VV23_CO2; // k_(030->001)^M ; VV_(2-3)
double kCO2_VV123_CO2; // k_(110->001)^(CO2) ; VV_(1-2-3)
double kCO2_VV12_CO2; // k_(100->020)^(CO2) ; VV_(1-2)
double kCO2_VV2CO; // k_(030->000)^(0->1) ; VV_(2-CO)
double kCO2_VV12CO; // k_(110->000)^(0->1) ; VV_(1-2-CO)
double kCO2_VV3CO; // k_(001->000)^(0-->1) ; VV_(3-CO)


vector<double> Eco (lCO+1);

vector<vector<vector<double> > > Eco2 (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > iCO2 (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));

vector<double> ACO2_VT2_CO2 (3);
vector<double> ACO2_VT2_N2 (3);
vector<double> ACO2_VT2_CO (3);
vector<double> ACO2_VT2_O2 (3);
vector<double> ACO2_VT2_O (3);
vector<double> ACO2_VV23_CO2 (3);
vector<double> ACO2_VV23_N2 (3);
vector<double> ACO2_VV23_CO (3);
vector<double> ACO2_VV23_O2 (3);
vector<double> ACO2_VV23_O (3);
vector<double> ACO2_VV2CO (3);
vector<double> ACO2_VV3CO (3);

vector<vector<vector<double> > > R_VT2_CO2_f (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VT2_CO2_b (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VT2_CO_f (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VT2_CO_b (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VT2_O2_f (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VT2_O2_b (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VT2_O_f (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VT2_O_b (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));

vector<vector<vector<double> > > R_VV23_CO2_f (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VV23_CO2_b (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));

vector<vector<vector<double> > > R_VV123_CO2_f (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VV123_CO2_b (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));

vector<vector<vector<vector<double> > > > R_VV12CO_f (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));
vector<vector<vector<vector<double> > > > R_VV12CO_b (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));

vector<vector<vector<vector<double> > > > R_VV2CO_f (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));
vector<vector<vector<vector<double> > > > R_VV2CO_b (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));

vector<vector<vector<vector<double> > > > R_VV3CO_f (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));
vector<vector<vector<vector<double> > > > R_VV3CO_b (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));

vector<vector<vector<double> > > R_VV12_CO2_f (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));
vector<vector<vector<double> > > R_VV12_CO2_b (lCO2s+1, vector<vector<double> > (lCO2b+1, vector<double> (lCO2a+1)));

vector<vector<vector<vector<double> > > > R_diss_CO2_f (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));
vector<vector<vector<vector<double> > > > R_rec_CO2_b (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));
vector<vector<vector<vector<double> > > > R_diss_CO_f (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));
vector<vector<vector<vector<double> > > > R_rec_CO_b (lCO2s+1, vector<vector<vector<double> > > (lCO2b+1, vector<vector<double> > (lCO2a+1, vector<double> (lCO+1))));

double T;
cout << "T?";
cin >> T;

EnergiaVibrCO();
EnergiaVibrCO2();
CO2MixtureCoefficients_Rates();
RatesCO2(T);
writing(T);

double hc = 4.141d-12*2.997925d10;

return 0;
}

