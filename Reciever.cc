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

#include "Reciever.h"
#include "MyMessage_m.h"

Define_Module(Reciever);

void Reciever::initialize()
{
    // TODO - Generated method body
}

void Reciever::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    //std::cout << msg->getM_Payload()<<endl;
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);
    std::cout<< "Recived message: " <<mmsg->getM_Payload()<<endl;
    std::bitset<8> parity = (std::bitset<8>) 0;

    std::cout<<sizeof(mmsg->getM_Payload())<<endl;
    std::string ahmd = mmsg->getM_Payload();

    std::cout<< "text length:" << ahmd.size()<<endl;

    for(int i = 0 ; i < ahmd.size();i++)
    {
        parity = parity ^ (std::bitset<8>)mmsg->getM_Payload()[i];
    }

    if(parity == mmsg->getMycheckbits())
        {
            mmsg->setM_Type(1);
        }
        else
        {
            mmsg->setM_Type(0);
        }

    send(mmsg,"out");
}
