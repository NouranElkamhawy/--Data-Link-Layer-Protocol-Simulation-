//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __LAB4_STUDENT_NODE0_H_
#define __LAB4_STUDENT_NODE0_H_

#include <omnetpp.h>
#include <fstream>
#include<iostream>
#include <sstream>
#include<string>
#include <vector>
#include <bitset>
#include <time.h>
#include <fstream>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node0 : public cSimpleModule
{
public:
    static std::ofstream myFile;
    static std::ofstream myFile1;
    static std::ofstream myFile2;
    //static std::ofstream file;

  protected:
    int count;
    int started;
    int index;
    bool sender;
    int RecivedSeqNumber;
    double begTime;
    bool Dubprint;
    int Dubindex;
    bool DubModification;
    int TotalDubs;
    int S_st_index;
    int S_end_index;
    int S_curr;
    int R_st_index;
    int R_end_index;
    int R_curr;
    bool finish;
    std::vector<std::string> mesgs;
    std::vector<int> REC;
    std::vector<bool> again;
    bool timeOut;
    bool NackRecived;
    int Ack_Nack_Id;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual std::string xor1(std::string a, std::string b);
    virtual std::string mod2div(std::string divident, std::string divisor);

};

#endif
