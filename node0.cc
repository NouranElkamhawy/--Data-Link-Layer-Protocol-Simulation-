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

#include "node0.h"
#include "MyMessage_m.h"
#include<iostream>
#include<algorithm>
#include<vector>
#include<bitset>
using namespace std;

//#include <vector>

Define_Module(Node0);

std::ofstream Node0::myFile;
std::ofstream Node0::myFile1;
std::ofstream Node0::myFile2;

bitset<1> getP(int pIndex, int size, vector<bitset<1>> msg) {
    bitset<1> P = 0;

    int copyIndex = pIndex;
    while (copyIndex < size) {
        for (int i = copyIndex; i < copyIndex + pIndex; i++) {
            if (i == msg.size()) {
                break;
            }
            P = P ^ msg[i];
        }
        copyIndex += pIndex * 2;
    }
    return P;
}

vector<bitset<1>> hammingCode(string msg) {
    int r = 0;
    // string modMsg = "";

    while (pow(2, r) < (msg.size() + r + 1)) {
        r++;
    }
    vector<bitset<1>> modMsg(msg.size() + r + 1, 1);
    for (int i = 0; i < r; i++) {
        modMsg[pow(2, i)] = 0;
    }
    int msgIndex = 0;
    for (int i = 1; i < msg.size() + r + 1; i++) {
        if (modMsg[i] == 1) {
            modMsg[i] = msg[msgIndex];
            msgIndex++;
        }
    }
    /*for (int i = 0; i < modMsg.size(); i++)
     {
     cout << " t " << modMsg[i] << endl;
     }*/
    vector<bitset<1>> allP(r);
    for (int i = 0; i < r; i++) {
        allP[i] = getP(pow(2, i), msg.size() + r + 1, modMsg);
    }
    return allP;
    /*for (int i = 1; i < r+1;i++)
     {
     for (int j = pow(2, i); j < msg.size() + r + 1; j = j + i)
     {

     }
     }*/

    /*for (int i = 0; i < msg.size() + r; i++)
     {
     if(pow(2,i)%)
     modMsg[i]=
     }*/
}

int changedBit(int number) {
    int count = 0;
    while (pow(2, count) < number) {
        count++;
    }
    return number - count;
}

void Node0::initialize() {
    Ack_Nack_Id = 0;
    NackRecived = false;
    finish = false;
    //timeOut
    S_st_index = 0;
    S_end_index = getParentModule()->par("window").intValue();
    S_curr = 0;
    R_st_index = 0;
    R_end_index = getParentModule()->par("window").intValue();
    R_curr = 0;
    /*R_st_index = 0;
     R_end_index = getParentModule()->par("window").intValue();
     R_curr = 0;*/
    TotalDubs = 0;
    count = 0;
    started = 0;
    index = 0;
    sender = false;
    RecivedSeqNumber = -1;
    Dubprint = false;
    // TODO - Generated method body
    begTime = clock();

    if (!Node0::myFile.is_open()) {
        Node0::myFile.open("pair01.txt", std::ios::out);
        if (!Node0::myFile) {
            std::cout << "File not created!";
        } else {
            std::cout << "log File created successfully!";
        }
    }

    if (!Node0::myFile1.is_open()) {
        Node0::myFile1.open("pair23.txt", std::ios::out);
        if (!Node0::myFile1) {
            std::cout << "File not created!";
        } else {
            std::cout << "log File created successfully!";
        }
    }

    if (!Node0::myFile2.is_open()) {
        Node0::myFile2.open("pair45.txt", std::ios::out);
        if (!Node0::myFile2) {
            std::cout << "File not created!";
        } else {
            std::cout << "log File created successfully!";
        }
    }

}

void Node0::handleMessage(cMessage *msg) {
    if (finish) {
        return;
    }
    //if(msg)

    if (Dubprint) {
        std::cout << "\nit must enter here at dublication \n" << endl;
        Dubprint = false;
        MyMessage_Base *Nmsg = check_and_cast<MyMessage_Base *>(msg);
        std::string ToSend = Nmsg->getM_Payload();
        bool Modification = false;
        if (mesgs[index][0] == '1') {
            std::cout << "\nit must enter here at Modification \n" << endl;
            Modification = true;
        }
        if (DubModification) {
            /*std::cout<<"\nit must enter here at dublication and modification \n"<<endl;

             //printed = printed + "with Modification";
             std::cout << " - node" << getIndex() << " sends message with id="
             << Dubindex << " and content=\"" << ToSend << "\" at "
             << simTime() << " with Modification" << endl;*/

            if (getIndex() <= 1) {
                Node0::myFile << "- node" << getIndex()
                        << " sends message with id=" << Dubindex
                        << " and content=\"" << ToSend << "\" at " << simTime()
                        << " with Modification" << std::endl;
            } else if (getIndex() <= 3) {
                Node0::myFile1 << "- node" << getIndex()
                        << " sends message with id=" << Dubindex
                        << " and content=\"" << ToSend << "\" at " << simTime()
                        << " with Modification" << std::endl;
            } else {
                Node0::myFile2 << "- node" << getIndex()
                        << " sends message with id=" << Dubindex
                        << " and content=\"" << ToSend << "\" at " << simTime()
                        << " with Modification" << std::endl;
            }

        } else {
            /*std::cout<<"\nit must enter here at dublication only \n"<<endl;

             std::cout << "- node" << getIndex() << " sends message with id="
             << Dubindex << " and content=\"" << ToSend << "\" at "
             << simTime() << endl;*/
            if (getIndex() <= 1) {
                Node0::myFile << "- node" << getIndex()
                        << " sends message with id=" << Dubindex
                        << " and content=\"" << ToSend << "\" at " << simTime()
                        << std::endl;
            } else if (getIndex() <= 3) {
                Node0::myFile1 << "- node" << getIndex()
                        << " sends message with id=" << Dubindex
                        << " and content=\"" << ToSend << "\" at " << simTime()
                        << std::endl;
            } else {
                Node0::myFile2 << "- node" << getIndex()
                        << " sends message with id=" << Dubindex
                        << " and content=\"" << ToSend << "\" at " << simTime()
                        << std::endl;
            }
            delete Nmsg;
        }
        return;
    }
    if (started == 0) {
        std::string MyMsg = msg->getName();
        int node;
        std::string FileName = "";
        std::string start;
        int TimeToStart;
        node = stoi(MyMsg);
        //FileName = "";
        FileName = FileName + MyMsg[2] + MyMsg[3] + MyMsg[4] + MyMsg[5]
                + MyMsg[6] + MyMsg[7] + MyMsg[8] + MyMsg[9] + MyMsg[10]
                + MyMsg[11];

        if (MyMsg.size() >= 20) {
            TimeToStart = stoi(MyMsg.substr(19, MyMsg.size() - 19));
            /*std::cout << TimeToStart << endl;*/
            sender = true;
        }

        std::string filename =
                "C:/Users/ammar/Desktop/omnetpp-5.4.1/samples/Lab4_Student/src/input"
                        + std::to_string(getIndex()) + ".txt";

        std::ifstream inFile(filename);

        if (inFile.is_open()) {
            /*std::cout << "The file is opened successfully" << endl;*/
        }

        if (!inFile) {
            /*std::cout << "Unable to open file";*/
            exit(1); // terminate with error
        }

        //std::vector<std::string> mesgs;

        std::string str;
        int x = 0;
        while (std::getline(inFile, str)) {
            mesgs.push_back(str);
        }

        for (int i = 0; i < mesgs.size(); i++) {
            again.push_back(true);
        }

        /*std::cout << node << endl << FileName << endl;*/

        /*for (int i = 0; i < mesgs.size(); i++) {
         /*std::cout << mesgs[i] << endl;
         }*/
        started = 1;
        if (sender) {
            scheduleAt(TimeToStart, new MyMessage_Base());
        } else {
            for (int i = 0; i < 100; i++) {
                REC.push_back(-1);
            }

        }
        /*std::cout << "in recive node " << getIndex() << "\t" << sender << endl;*/
        return;
    }
    if (sender) {
        if (finish != 1) {
            //if(index == mesgs.size())
            //    return;

            if (NackRecived) {

                NackRecived = false;

                ///////////////////////////////////////       creating new message    /////////////////////////

                MyMessage_Base* Nmsg = new MyMessage_Base;

                //////////////////////////////////////     Byte stuffing and crc    ////////////////////////////

                std::vector<char> PerformCheck;
                std::string sending;
                sending = (mesgs[Ack_Nack_Id].substr(5,
                        mesgs[Ack_Nack_Id].size() - 5));
                PerformCheck.push_back('$');
                for (int i = 0; i < sending.size(); i++) {
                    if (sending[i] == '$' || sending[i] == '/') {
                        PerformCheck.push_back('/');
                    }
                    PerformCheck.push_back(sending[i]);
                }
                PerformCheck.push_back('$');
                std::string ToSend = "";
                for (int i = 0; i < PerformCheck.size(); i++) {
                    ToSend = ToSend + PerformCheck[i];
                }
                Nmsg->setSeq_Num(Ack_Nack_Id);
                Nmsg->setSendingTime(simTime().dbl());
                std::string msgbits = "";
                for (int i = 0; i < ToSend.size(); i++) {
                    std::bitset<8> b(ToSend[i]);
                    msgbits = msgbits + b.to_string();
                }
                std::string divisor = "101010101";
                std::string CRC = mod2div(msgbits + "00000000", divisor);
                std::bitset<8> CRCbits(CRC);
                //std::cout << CRC << "\t" << CRCbits << endl;
                Nmsg->setMycheckbits(CRCbits);

                string str = ToSend.c_str();
                string MessageToSend = "";
                for (int i = 0; i < str.length(); ++i) {
                    bitset<8> bs4(str[i]);

                    MessageToSend += bs4.to_string();

                    //cout << bs4;
                }
                //co<<ut" hamming code message to send is "
                vector<bitset<1>> vec = hammingCode(MessageToSend);
                cout << endl;
                for (int i = 0; i < vec.size(); i++) {
                    cout << vec[i];
                }
                cout << endl;
                Nmsg->setMyHammingCode(hammingCode(MessageToSend));
                ///////////////////////////////////// payload setting //////////////////////////////////

                Nmsg->setM_Payload(ToSend.c_str());

                //////////////////////////////////// printitng section //////////////////////////////////

                if (getIndex() <= 1) {
                    Node0::myFile << "- node" << getIndex()
                            << " sends message with id=" << Ack_Nack_Id
                            << " and content=\"" << ToSend << "\" at "
                            << simTime() << std::endl;
                } else if (getIndex() <= 3) {
                    Node0::myFile1 << "- node" << getIndex()
                            << " sends message with id=" << Ack_Nack_Id
                            << " and content=\"" << ToSend << "\" at "
                            << simTime() << std::endl;
                } else {
                    Node0::myFile2 << "- node" << getIndex()
                            << " sends message with id=" << Ack_Nack_Id
                            << " and content=\"" << ToSend << "\" at "
                            << simTime() << std::endl;
                }

                ////////////////////////////////// Sending section ///////////////////////////////////////////

                send(Nmsg, "out");
                MyMessage_Base* MyDubMsg = new MyMessage_Base;
                MyDubMsg->setSeq_Num(Nmsg->getSeq_Num());
                MyDubMsg->setSendingTime(Nmsg->getSendingTime());
                MyDubMsg->setM_Payload(Nmsg->getM_Payload());
                MyDubMsg->setMycheckbits(Nmsg->getMycheckbits());
                MyDubMsg->setM_Type(2);
                MyDubMsg->setAckID(Nmsg->getAckID());
                simtime_t t = 0.12;
                scheduleAt(simTime() + t, MyDubMsg);

                scheduleAt(simTime() + 0.02, new MyMessage_Base());

                return;

                ////////////////////////////////////////////////////////////////////////////////////////

            }

            std::cout << "index = " << index << endl;
            ;
            begTime = clock();
            MyMessage_Base *Nmsg;
            if (started == 1) {

                //Nmsg = new MyMessage_Base;
                started = 2;
            } else if (!msg->isSelfMessage()) {
                Nmsg = check_and_cast<MyMessage_Base *>(msg);
                if (Nmsg->getM_Type() == 1) {
                    if (getIndex() <= 1) {
                        myFile << "Ack recived is " << Nmsg->getM_Type()
                                << " with id = " << Nmsg->getAckID() + 1
                                << " at time " << simTime() << " index = "
                                << index << endl;
                    } else if (getIndex() <= 3) {
                        myFile1 << "Ack recived is " << Nmsg->getM_Type()
                                << " with id = " << Nmsg->getAckID() + 1
                                << " at time " << simTime() << endl;
                    } else {
                        myFile2 << "Ack recived is " << Nmsg->getM_Type()
                                << " with id = " << Nmsg->getAckID() + 1
                                << " at time " << simTime() << endl;
                    }
                } else {
                    if (getIndex() <= 1) {
                        myFile << "NAck recived is " << Nmsg->getM_Type()
                                << " with id = " << Nmsg->getAckID() + 1
                                << " at time " << simTime() << endl;
                    } else if (getIndex() <= 3) {
                        myFile1 << "NAck recived is " << Nmsg->getM_Type()
                                << " with id = " << Nmsg->getAckID() + 1
                                << " at time " << simTime() << endl;
                    } else {
                        myFile2 << "NAck recived is " << Nmsg->getM_Type()
                                << " with id = " << Nmsg->getAckID() + 1
                                << " at time " << simTime() << endl;
                    }
                }
                if (Nmsg->getM_Type() == 1) {
                    count++;
                }
                int ackid = Nmsg->getAckID() + 1;
                //again[ackid - 1] = false;
                int AckVal = Nmsg->getM_Type();
                std::cout << ackid << endl;
                if (ackid == mesgs.size()) {
                    finish = true;
                    return;
                }
                if (S_st_index < ackid) {
                    S_st_index = ackid;
                    while (again[index] == false) {
                        index++;
                        if (index == mesgs.size()) {
                            index--;
                            break;
                        }
                    }
                }
                if (AckVal == 0) {

                    NackRecived = true;
                    Ack_Nack_Id = ackid;
                    return;
                }
                S_end_index = S_st_index
                        + getParentModule()->par("window").intValue();
                if (S_end_index > mesgs.size()) {
                    S_end_index = mesgs.size();
                }
                if (index < S_st_index) {
                    index = S_st_index;
                }
                //index = S_st_index;
                myFile << S_st_index << "\t" << index << "\t" << S_end_index
                        << endl;
                return;
            }
            if (msg->isSelfMessage()) {
                Nmsg = check_and_cast<MyMessage_Base *>(msg);
                if (Nmsg->getM_Type() == 2) {
                    if (Nmsg->getSeq_Num() >= S_st_index) {

                        std::vector<char> PerformCheck;
                        std::string sending;
                        sending = (mesgs[Nmsg->getSeq_Num()].substr(5,
                                mesgs[Nmsg->getSeq_Num()].size() - 5));
                        PerformCheck.push_back('$');
                        for (int i = 0; i < sending.size(); i++) {
                            if (sending[i] == '$' || sending[i] == '/') {
                                PerformCheck.push_back('/');
                            }
                            PerformCheck.push_back(sending[i]);
                        }
                        PerformCheck.push_back('$');
                        std::string ToSend = "";
                        for (int i = 0; i < PerformCheck.size(); i++) {
                            ToSend = ToSend + PerformCheck[i];
                        }

                        if (getIndex() <= 1) {
                            Node0::myFile << "- node" << getIndex()
                                    << " sends message with id="
                                    << Nmsg->getSeq_Num() << " and content=\""
                                    << Nmsg->getM_Payload() << "\" at "
                                    << simTime() << std::endl;
                        } else if (getIndex() <= 3) {
                            Node0::myFile1 << "- node" << getIndex()
                                    << " sends message with id="
                                    << Nmsg->getSeq_Num() << " and content=\""
                                    << ToSend << "\" at " << simTime()
                                    << std::endl;
                        } else {
                            Node0::myFile2 << "- node" << getIndex()
                                    << " sends message with id="
                                    << Nmsg->getSeq_Num() << " and content=\""
                                    << ToSend << "\" at " << simTime()
                                    << std::endl;
                        }
                        send(Nmsg, "out");
                        MyMessage_Base* MyDubMsg = new MyMessage_Base;
                        MyDubMsg->setSeq_Num(Nmsg->getSeq_Num());
                        MyDubMsg->setSendingTime(Nmsg->getSendingTime());
                        MyDubMsg->setM_Payload(Nmsg->getM_Payload());
                        MyDubMsg->setMycheckbits(Nmsg->getMycheckbits());
                        MyDubMsg->setM_Type(2);
                        MyDubMsg->setAckID(Nmsg->getAckID());
                        simtime_t t = 0.12;
                        scheduleAt(simTime() + t, MyDubMsg);
                        return;
                    }
                    return;
                }
            }
            Nmsg = new MyMessage_Base;
            bool Modification = false, lose = false, Dublication = false,
                    delay = false;
            if (mesgs[index][0] == '1') {
                Modification = true;
            }
            if (mesgs[index][1] == '1') {
                lose = true;
            }
            if (mesgs[index][2] == '1') {
                Dublication = true;
            }
            if (mesgs[index][3] == '1') {
                delay = true;
            }
            std::vector<char> PerformCheck;
            std::string sending;
            sending = (mesgs[index].substr(5, mesgs[index].size() - 5));
            PerformCheck.push_back('$');
            for (int i = 0; i < sending.size(); i++) {
                if (sending[i] == '$' || sending[i] == '/') {
                    PerformCheck.push_back('/');
                }
                PerformCheck.push_back(sending[i]);
            }
            PerformCheck.push_back('$');
            std::string ToSend = "";
            for (int i = 0; i < PerformCheck.size(); i++) {
                ToSend = ToSend + PerformCheck[i];
            }
            Nmsg->setSeq_Num(index);
            Nmsg->setSendingTime(simTime().dbl());
            std::string msgbits = "";
            for (int i = 0; i < ToSend.size(); i++) {
                std::bitset<8> b(ToSend[i]);
                msgbits = msgbits + b.to_string();
            }
            std::string divisor = "101010101";
            std::string CRC = mod2div(msgbits + "00000000", divisor);
            std::bitset<8> CRCbits(CRC);
            //std::cout << CRC << "\t" << CRCbits << endl;
            Nmsg->setMycheckbits(CRCbits);

            ///////////////////////////////////////////////
            string str = ToSend.c_str();
            string MessageToSend = "";
            for (int i = 0; i < str.length(); ++i) {
                bitset<8> bs4(str[i]);

                MessageToSend += bs4.to_string();

                //cout << bs4;
            }
            //co<<ut" hamming code message to send is "
            vector<bitset<1>> vec = hammingCode(MessageToSend);
            cout << endl;
            for (int i = 0; i < vec.size(); i++) {
                cout << vec[i];
            }
            cout << endl;
            Nmsg->setMyHammingCode(hammingCode(MessageToSend));

            ///////////////////////////////////////////////

            std::string corect;
            corect = ToSend;
            if (Modification) {
                int modindx = (par("guess").doubleValue() / 10.0)
                        * ToSend.size();
                //std::cout << ToSend[modindx] << "\t";

                //myFile<<"to send = "<<ToSend<<endl;
                //myFile<<"to corect = "<<corect<<endl;
                ToSend[modindx] = !ToSend[modindx];// + 1;
                //std::cout << ToSend[modindx] << endl;
            }
            Nmsg->setM_Payload(ToSend.c_str());
            bool result = false;
            for (int i = S_st_index; i < S_end_index; i++) {
                result = result || again[i];
            }
            if (!lose && !delay && result) {
                //std::string printed = "node" +std::to_string(getIndex())+" sends message with id="+std::to_string(index)+" and content=\"" + ToSend + "\" at " + std::to_string(simTime());
                if (Modification) {
                    //printed = printed + "with Modification";
                    /*std::cout << " - node" << getIndex()
                     << " sends message with id=" << index
                     << " and content=\"" << ToSend << "\" at "
                     << simTime() << " with Modification" << endl;*/
                    if (getIndex() <= 1) {
                        Node0::myFile << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << " with Modification"
                                << std::endl;
                    } else if (getIndex() <= 3) {
                        Node0::myFile1 << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << " with Modification"
                                << std::endl;
                    } else {
                        Node0::myFile2 << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << " with Modification"
                                << std::endl;
                    }
                } else {
                    /*std::cout << "- node" << getIndex()
                     << " sends message with id=" << index
                     << " and content=\"" << ToSend << "\" at "
                     << simTime() << endl;*/
                    if (getIndex() <= 1) {
                        Node0::myFile << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << std::endl;
                    } else if (getIndex() <= 3) {
                        Node0::myFile1 << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << std::endl;
                    } else {
                        Node0::myFile2 << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << std::endl;
                    }
                }
                /*if(again[index] == true)
                 {
                 send(Nmsg, "out");
                 }
                 else
                 {
                 /*MyMessage_Base* MytimeMsg = new MyMessage_Base;
                 MytimeMsg->setM_Type(2);
                 MytimeMsg->setSeq_Num(index);
                 Nmsg->setM_Type(2);
                 simtime_t t = 0.12;
                 scheduleAt(simTime() + t, Nmsg);
                 }*/

                send(Nmsg, "out");
                MyMessage_Base* MyDubMsg = new MyMessage_Base;
                MyDubMsg->setSeq_Num(Nmsg->getSeq_Num());
                MyDubMsg->setSendingTime(Nmsg->getSendingTime());
                MyDubMsg->setM_Payload(corect.c_str());
                //myFile << "corect = " << corect << endl;
                MyDubMsg->setMycheckbits(Nmsg->getMycheckbits());
                MyDubMsg->setM_Type(2);
                MyDubMsg->setAckID(Nmsg->getAckID());
                simtime_t t = 0.12;
                scheduleAt(simTime() + t, MyDubMsg);
                //Nmsg->setM_Type(0);
            }
            if (Dublication) {

                TotalDubs = TotalDubs + 1;
                Dubprint = true;
                MyMessage_Base* MyDubMsg = new MyMessage_Base;
                MyDubMsg->setSeq_Num(Nmsg->getSeq_Num());
                MyDubMsg->setSendingTime(Nmsg->getSendingTime());
                MyDubMsg->setM_Payload(Nmsg->getM_Payload());
                MyDubMsg->setMycheckbits(Nmsg->getMycheckbits());
                MyDubMsg->setM_Type(Nmsg->getM_Type());
                MyDubMsg->setAckID(Nmsg->getAckID());
                Dubindex = index;
                DubModification = Modification;
                scheduleAt(simTime() + 0.01, MyDubMsg);

                MyMessage_Base* Dmsg = new MyMessage_Base;
                Dmsg->setSeq_Num(Nmsg->getSeq_Num());
                Dmsg->setSendingTime(Nmsg->getSendingTime());
                Dmsg->setM_Payload(Nmsg->getM_Payload());
                Dmsg->setMycheckbits(Nmsg->getMycheckbits());
                Dmsg->setM_Type(Nmsg->getM_Type());
                Dmsg->setAckID(Nmsg->getAckID());
                simtime_t t = 0.01;
                sendDelayed(Dmsg, t, "out");

                MyMessage_Base* MyDubMsg2 = new MyMessage_Base;
                MyDubMsg2->setSeq_Num(Nmsg->getSeq_Num());
                MyDubMsg2->setSendingTime(Nmsg->getSendingTime());
                MyDubMsg2->setM_Payload(corect.c_str());
                //myFile << "corect = " << corect << endl;
                MyDubMsg2->setMycheckbits(Nmsg->getMycheckbits());
                MyDubMsg2->setM_Type(2);
                MyDubMsg2->setAckID(Nmsg->getAckID());
                simtime_t t2 = 0.12;
                scheduleAt(simTime() + t2 + t, MyDubMsg2);

                /*if (Modification) {
                 //printed = printed + "with Modification";
                 std::cout << " - node" << getIndex()
                 << " sends message with id=" << index
                 << " and content=\"" << ToSend << "\" at "
                 << simTime() << " with Modification" << endl;
                 Node0::myFile << "- node" << getIndex()
                 << " sends message with id=" << index
                 << " and content=\"" << ToSend << "\" at "
                 << simTime() << " with Modification" << std::endl;
                 } else {
                 std::cout << "- node" << getIndex()
                 << " sends message with id=" << index
                 << " and content=\"" << ToSend << "\" at "
                 << simTime() << endl;
                 Node0::myFile << "- node" << getIndex()
                 << " sends message with id=" << index
                 << " and content=\"" << ToSend << "\" at "
                 << simTime() << std::endl;
                 }*/
            }
            if (delay) {
                if (Modification) {
                    //printed = printed + "with Modification";
                    /*std::cout << "- node" << getIndex()
                     << " sends message with id=" << index
                     << " and content=\"" << ToSend << "\" at "
                     << simTime() << " with Modification" << endl;*/
                    if (getIndex() <= 1) {
                        Node0::myFile << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << " with Modification"
                                << std::endl;
                    } else if (getIndex() <= 3) {
                        Node0::myFile1 << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << " with Modification"
                                << std::endl;
                    } else {
                        Node0::myFile2 << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << " with Modification"
                                << std::endl;
                    }
                } else {
                    /*std::cout << "- node" << getIndex()
                     << " sends message with id=" << index
                     << " and content=\"" << ToSend << "\" at "
                     << simTime() << endl;*/
                    if (getIndex() <= 1) {
                        Node0::myFile << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << std::endl;
                    } else if (getIndex() <= 3) {
                        Node0::myFile1 << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << std::endl;
                    } else {
                        Node0::myFile2 << "- node" << getIndex()
                                << " sends message with id=" << index
                                << " and content=\"" << ToSend << "\" at "
                                << simTime() << std::endl;
                    }
                }
                //simtime_t t = 0.1;
                double del = getParentModule()->par("delay").doubleValue();
                //std::cout << "del val = " << del << endl;
                sendDelayed(Nmsg, del, "out");
                MyMessage_Base* MyDubMsg = new MyMessage_Base;
                MyDubMsg->setSeq_Num(Nmsg->getSeq_Num());
                MyDubMsg->setSendingTime(Nmsg->getSendingTime());
                MyDubMsg->setM_Payload(corect.c_str());
                //myFile << "corect = " << corect << endl;
                MyDubMsg->setMycheckbits(Nmsg->getMycheckbits());
                MyDubMsg->setM_Type(2);
                MyDubMsg->setAckID(Nmsg->getAckID());
                simtime_t t = 0.12;
                scheduleAt(simTime() + t, MyDubMsg);

            }
            if (lose) {
                if (getIndex() <= 1) {
                    Node0::myFile << "- node" << getIndex()
                            << " sends message with id=" << index
                            << " and content=\"" << ToSend << "\" at "
                            << simTime() << std::endl;
                } else if (getIndex() <= 3) {
                    Node0::myFile1 << "- node" << getIndex()
                            << " sends message with id=" << index
                            << " and content=\"" << ToSend << "\" at "
                            << simTime() << std::endl;
                } else {
                    Node0::myFile2 << "- node" << getIndex()
                            << " sends message with id=" << index
                            << " and content=\"" << ToSend << "\" at "
                            << simTime() << std::endl;
                }            //scheduleAt(simTime() + 0.03, Nmsg);
                lose = false;
                mesgs[index][1] = '0';
                MyMessage_Base* MyDubMsg = new MyMessage_Base;
                MyDubMsg->setSeq_Num(Nmsg->getSeq_Num());
                MyDubMsg->setSendingTime(Nmsg->getSendingTime());
                MyDubMsg->setM_Payload(corect.c_str());
                //myFile << "corect = " << corect << endl;
                MyDubMsg->setMycheckbits(Nmsg->getMycheckbits());
                MyDubMsg->setM_Type(2);
                MyDubMsg->setAckID(Nmsg->getAckID());
                simtime_t t = 0.12;
                scheduleAt(simTime() + t, MyDubMsg);
                //return we decided to send the nest message based on the document page 3
                //return;
            }
            again[index] = false;
            mesgs[index][0] = 0;
            mesgs[index][1] = 0;
            mesgs[index][2] = 0;
            mesgs[index][3] = 0;
            index++;
            if (index >= S_end_index) {
                //std::cout << "Entered this if" << endl;
                //index = S_st_index;
                index = S_end_index - 1;
                //return;
            }
            /*bool result = false;
             for(int i = S_st_index ; i < S_end_index;i++)
             {
             result = result || again[i];
             }
             if(!result)
             {
             return;
             }*/
            myFile << " index =  " << index << " at time = " << simTime()
                    << endl;
            scheduleAt(simTime() + 0.02, new MyMessage_Base());
        } else {
            if (getIndex() <= 1) {
                Node0::myFile << "- node" << getIndex() << " end of input file"
                        << std::endl;
                Node0::myFile << "total transmission time= " << simTime()
                        << std::endl;
                Node0::myFile << "total number of transmissions= "
                        << index + TotalDubs << std::endl;
                Node0::myFile << "the network throughput= "
                        << (double) count / simTime() << std::endl;
                myFile.close();
            } else if (getIndex() <= 3) {
                Node0::myFile1 << "- node" << getIndex() << " end of input file"
                        << std::endl;
                Node0::myFile1 << "total transmission time= " << simTime()
                        << std::endl;
                Node0::myFile1 << "total number of transmissions= "
                        << index + TotalDubs << std::endl;
                Node0::myFile1 << "the network throughput= "
                        << (double) count / simTime() << std::endl;
                myFile1.close();
            } else {
                Node0::myFile2 << "- node" << getIndex() << " end of input file"
                        << std::endl;
                Node0::myFile2 << "total transmission time= " << simTime()
                        << std::endl;
                Node0::myFile2 << "total number of transmissions= "
                        << index + TotalDubs << std::endl;
                Node0::myFile2 << "the network throughput= "
                        << (double) count / simTime() << std::endl;
                myFile2.close();
            }
        }

    } /*     RECIVER START     */
    else {
        bool Not_expected = false;
        //std::cout << "error" << endl;
        MyMessage_Base *Nmsg = check_and_cast<MyMessage_Base *>(msg);
        //Node0::myFile << "- node" << getIndex() << " sequence Number = "
        //      << Nmsg->getSeq_Num() << " end_index = " << R_end_index
        //    << " st index = " << R_st_index << " REC = "
        //  << REC[Nmsg->getSeq_Num()] << std::endl;
        std::string ahmd = Nmsg->getM_Payload();
        //std::cout << ahmd << endl << Nmsg->getSeq_Num() << endl
        //      << Nmsg->getSendingTime() << endl;
        std::string RecMessg = Nmsg->getM_Payload();
        std::string msgbits = "";

        for (int i = 0; i < RecMessg.size(); i++) {
            std::bitset<8> b(RecMessg[i]);
            msgbits = msgbits + b.to_string();
        }
        std::string divisor = "101010101";
        std::string CRC = mod2div(msgbits + "00000000", divisor);
        std::bitset<8> CRCbits(CRC);
        ////////// calcualating hamming /////////
        string str = Nmsg->getM_Payload();
        string MessageToSend = "";
        for (int i = 0; i < str.length(); ++i) {
            bitset<8> bs4(str[i]);

            MessageToSend += bs4.to_string();

            //cout << bs4;
        }
        vector<bitset<1>> p = hammingCode(MessageToSend);
        string recHammingString = "";
        string sendHammingString = "";
        for (int i = 0; i < p.size(); i++) {
            cout << "enter the for" << endl;
            recHammingString += p[i].to_string();
            cout << "enter the for and p size = " << p.size() << endl;
            cout << " ham of  0 = " << Nmsg->getMyHammingCode()[0] << endl;
            sendHammingString += Nmsg->getMyHammingCode()[i].to_string();
        }
        string comparison = xor1(recHammingString, sendHammingString);
        myFile << "comparison = " << comparison;
        //std::cout << CRC << "\t" << CRCbits << endl;
        if (CRCbits == Nmsg->getMycheckbits()) {
            /*std::cout<<"entered if"<<endl;
             std::cout << "- node" << getIndex() << " recieved message with id="
             << Nmsg->getSeq_Num() << " and content=\"" << RecMessg
             << "\" at " << simTime() << endl;*/
            if (getIndex() <= 1) {
                Node0::myFile << "- node" << getIndex()
                        << " recieved message with id=" << Nmsg->getSeq_Num()
                        << " and content=\"" << RecMessg << "\" at "
                        << simTime() << ", and piggybacking Ack number "
                        << Nmsg->getSeq_Num() + 1 << std::endl;
            } else if (getIndex() <= 3) {
                Node0::myFile1 << "- node" << getIndex()
                        << " recieved message with id=" << Nmsg->getSeq_Num()
                        << " and content=\"" << RecMessg << "\" at "
                        << simTime() << ", and piggybacking Ack number "
                        << Nmsg->getSeq_Num() + 1 << std::endl;
            } else {
                Node0::myFile2 << "- node" << getIndex()
                        << " recieved message with id=" << Nmsg->getSeq_Num()
                        << " and content=\"" << RecMessg << "\" at "
                        << simTime() << ", and piggybacking Ack number "
                        << Nmsg->getSeq_Num() + 1 << std::endl;
            }
        } else {
            /*std::cout<<"entered else"<<endl;
             std::cout << "- node" << getIndex() << " recieved message with id="
             << Nmsg->getSeq_Num() << " and content=\"" << RecMessg
             << "\" at " << simTime() << " with modification" << endl;*/
            if (getIndex() <= 1) {
                Node0::myFile << "- node" << getIndex()
                        << " recieved message with id=" << Nmsg->getSeq_Num()
                        << " and content=\"" << RecMessg << "\" at "
                        << simTime() << " with modification, "
                        << "and piggybacking NACK number "
                        << Nmsg->getSeq_Num() + 1 << std::endl;
            } else if (getIndex() <= 3) {
                Node0::myFile1 << "- node" << getIndex()
                        << " recieved message with id=" << Nmsg->getSeq_Num()
                        << " and content=\"" << RecMessg << "\" at "
                        << simTime() << " with modification, "
                        << "and piggybacking NACK number "
                        << Nmsg->getSeq_Num() + 1 << std::endl;
            } else {
                Node0::myFile2 << "- node" << getIndex()
                        << " recieved message with id=" << Nmsg->getSeq_Num()
                        << " and content=\"" << RecMessg << "\" at "
                        << simTime() << " with modification, "
                        << "and piggybacking NACK number "
                        << Nmsg->getSeq_Num() + 1 << std::endl;
            }

        }

        if (Nmsg->getSeq_Num() < R_end_index && Nmsg->getSeq_Num() >= R_st_index
                && REC[Nmsg->getSeq_Num()] != 1) {
            //RecivedSeqNumber = RecivedSeqNumber + 1;
            if (Nmsg->getSeq_Num() > R_st_index) {
                Not_expected = true;
            }
        } else {
            if (getIndex() <= 1) {
                Node0::myFile << "- node" << getIndex()
                        << " drops message with id=" << Nmsg->getSeq_Num()
                        << std::endl;
            } else if (getIndex() <= 3) {
                Node0::myFile1 << "- node" << getIndex()
                        << " drops message with id=" << Nmsg->getSeq_Num()
                        << std::endl;
            } else {
                Node0::myFile2 << "- node" << getIndex()
                        << " drops message with id=" << Nmsg->getSeq_Num()
                        << std::endl;
            }
            //std::cout<<"Recived dublicated message"<<endl;
            //delete Nmsg;
            int i;
            for (i = R_st_index; i < R_end_index; i++) {
                if (REC[i] != 1) {
                    std::cout << "R_st = " << R_st_index << " i = " << i
                            << endl;
                    break;
                }
            }
            Nmsg->setAckID(i - 1);
            simtime_t t = 0.05;
            Nmsg->setM_Type(0);
            sendDelayed(Nmsg, t, "out");
            return;
        }
        if (CRCbits == Nmsg->getMycheckbits()) {
            Nmsg->setM_Type(1);
        } else {
            //Node0::file << "- node" << getIndex()<< " drops message with id="<<Nmsg->getSeq_Num()<<std::endl;
            Nmsg->setM_Type(0);
            if (REC[Nmsg->getSeq_Num()] != 1) {
                REC[Nmsg->getSeq_Num()] = 0;
            }
        }
        Nmsg->setAckID(Nmsg->getSeq_Num());
        simtime_t t = 0.05;
        /*if(Nmsg->getSeq_Num() >= REC.size())
         {
         REC.push_back(Nmsg->getM_Type());
         }*/
        REC[Nmsg->getSeq_Num()] = Nmsg->getM_Type();
        /*for(int i = 0 ; i < 10;i++)
         {
         std::cout<<REC[i]<<"\t";
         }*/
        std::cout << endl;
        int i;
        for (i = 0; i <= R_end_index; i++) {
            if (REC[i] == -1 || REC[i] == 0) {
                std::cout << "R_st = " << R_st_index << " i = " << i << endl;
                R_st_index = i;
                break;
            }
        }
        R_end_index = R_st_index + getParentModule()->par("window").intValue();
        Nmsg->setAckID(R_st_index - 1);
        //simtime_t t = 0.05;
        if (REC[i] == -1) {
            if (Not_expected) {
                Nmsg->setM_Type(0);
            } else {
                Nmsg->setM_Type(1);

            }
        } else if (REC[i] == 0) {
            Nmsg->setM_Type(0);
        }
        //Nmsg->setM_Type(1);
        for (int i = 0; i < 5; i++) {
            std::cout << REC[i] << "\t";
        }
        std::cout << endl;
        sendDelayed(Nmsg, t, "out");
        //sendDelayed(Nmsg, t, "out");

    }
}

std::string Node0::xor1(std::string a, std::string b) {
    std::string result = "";
    int n = b.length();
    for (int i = 1; i < n; i++) {
        if (a[i] == b[i])
            result += "0";
        else
            result += "1";
    }
    return result;
}

std::string Node0::mod2div(std::string divident, std::string divisor) {
    int pick = divisor.length();
    std::string tmp = divident.substr(0, pick);
    int n = divident.length();
    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xor1(divisor, tmp) + divident[pick];
        else
            tmp = xor1(std::string(pick, '0'), tmp) + divident[pick];
        pick += 1;
    }
    if (tmp[0] == '1')
        tmp = xor1(divisor, tmp);
    else
        tmp = xor1(std::string(pick, '0'), tmp);
    return tmp;
}

