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

#include "coordinator.h"

Define_Module(Coordinator);

void Coordinator::initialize() {
    std::string Msg[6];
    int node;
    std::string FileName = "";
    std::string start;
    int TimeToStart;

    std::ifstream inFile(
            "C:/Users/ammar/Desktop/omnetpp-5.4.1/samples/Lab4_Student/src/coordinator.txt");

    if (inFile.is_open()) {
        std::cout << "The file is opened successfully" << endl;
    }

    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    std::string str;
    int x = 0;
    while (std::getline(inFile, str)) {
        Msg[x] = str;
        x++;
        node = stoi(str);
        FileName = "";
        FileName = FileName + str[2] + str[3] + str[4] + str[5] + str[6]
                + str[7] + str[8] + str[9] + str[10] + str[11];
    }

    // TODO - Generated method body
    /*cMessage *msg = new cMessage;
    //std::cout<<Msg[0]<<endl;
    msg->setName(Msg[0].c_str());
    //msg->setName("Nouran");
    send(msg, "outs", 0);
    cMessage *mmsg = new cMessage;
    mmsg->setName(Msg[1].c_str());
    send(mmsg, "outs", 1);*/
    //std::cout<<Msg[0]<<endl;
    for(int i = 0 ; i < 2 ; i++)
    {
        cMessage *msg = new cMessage;
        msg->setName(Msg[i].c_str());
        //std::cout<<Msg[i]<<endl;
        send(msg, "outs", i);
    }

}

void Coordinator::handleMessage(cMessage *msg) {
    // TODO - Generated method body
}
void Coordinator::ReadFile() {
    std::string Msg[2];
    int node;
    std::string FileName = "";
    std::string start;
    int TimeToStart;

    // int sum = 0;
    //  int x;
    std::ifstream inFile(
            "C:/Users/ammar/Desktop/omnetpp-5.4.1/samples/Lab4_Student/src/coordinator.txt");
    //std::ifstream inFile("input/test.txt");
    //inFile.open("test.txt");
    if (inFile.is_open()) {
        std::cout << "The file is opened successfully" << endl;
    }
    //inFile.open("test.txt");
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    std::string str;
    int x = 0;
    while (std::getline(inFile, str)) {
        Msg[x] = str;
        std::cout<<node<<" "<<Msg[x]<<endl;
        x++;
        node = stoi(str);
        FileName = "";
        FileName = FileName + str[2] + str[3] + str[4] + str[5] + str[6]
                + str[7] + str[8] + str[9] + str[10] + str[11];

        if (str.size() >= 20) {
            TimeToStart = stoi(str.substr(19, str.size() - 19));
            std::cout << TimeToStart << endl;
        }
        /*cMessage *msg = new cMessage;
        msg->setName(Msg[x-1].c_str());
        send(msg, "outs", node);*/
        // std::string nodeString=str[0];
        //  if((int)str[0]>=48 && (int)str[0]<=57)
        // {
        //     node =(int)str[0]-48;
        //   }

        //std::cout<<node<<endl;

        // std::cout<<FileName<<endl;
//std::cout<<str.size()<<" "<<x<<endl;
//x++;

    }
    std::cout<<node<<" "<<Msg[x]<<endl;
    //std::cout << Msg[0] << endl << Msg[1] << endl;
    //while (inFile >> x) {
    //  sum = sum + x;
    //   }
    //  std::cout << "Sum = " << sum << endl;
    // inFile.close();
}
