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

#include "Sender.h"
#include "MyMessage_m.h"

Define_Module(Sender);

void Sender::initialize()
{
    first = true;
    scheduleAt(simTime() + 5, new cMessage(""));
    /*std::cout<<"Enter a word : ";
            std::cin>>word;
            std::cout<<word<<endl;

            //2) calculate the char count

            int size = word.size() + 2;
            std::cout<<size<<endl;

            std::bitset<8> msgsize(size);

            word = (char)msgsize.to_ulong() + word;

            double MyGuess = par("guess").doubleValue();
            if(MyGuess > 5)
            {
                std::cout<<"entering false state"<<endl;
                word[1] +=1;
            }


            std::cout<<word<<endl;
            MyMessage_Base * mmsg = new MyMessage_Base("Hello");
            mmsg->setM_Payload(word.c_str());
            std::bitset<8> parity = (std::bitset<8>) 0;

            parity = parity ^ (std::bitset<8>)size;

            for(int i = 0 ; i < size -2;i++)
            {
                parity = parity ^ (std::bitset<8>)word[i];
            }

            mmsg->setM_Type(1);
            mmsg->setSeq_Num(0);

            mmsg->setMycheckbits(parity);
            send(mmsg,"out");*/

    // TODO - Generated method body
}

void Sender::handleMessage(cMessage *msg)
{

    MyMessage_Base *mmsg;
    if(!first)
    {
        mmsg = check_and_cast<MyMessage_Base *>(msg);
    }
    else
    {
        mmsg = new MyMessage_Base("Hello");
    }


    if(!first)
    {
        if(mmsg->getM_Type() == 0)
        {
            std::cout<<"error"<<endl;
        }
        else
        {
            std::cout<<"correct"<<endl;
        }
    }

    // TODO - Generated method body
    std::cout<<"Enter a word : ";
                std::cin>>word;
                std::cout<<word<<endl;

                //2) calculate the char count

                int size = word.size() + 2;
                std::cout<<size<<endl;

                std::bitset<8> msgsize(size);

                word = (char)msgsize.to_ulong() + word;




                std::cout<<word<<endl;
                //MyMessage_Base * mmsg = new MyMessage_Base("Hello");
                std::bitset<8> parity = (std::bitset<8>) 0;

                parity = parity ^ (std::bitset<8>)size;

                for(int i = 1 ; i < size -1;i++)
                {
                    parity = parity ^ (std::bitset<8>)word[i];
                }

                std::cout<<"parity to send is "<<parity<<endl;

                double MyGuess = par("guess").doubleValue();
                std::cout<<"my guess is "<<MyGuess<<endl;
                if(MyGuess > 5)
                {
                    std::cout<<"entering false state"<<endl;
                    word[1] +=1;
                }
                mmsg->setM_Payload(word.c_str());

                mmsg->setM_Type(1);
                if(first)
                {
                    mmsg->setSeq_Num(0);
                    first = false;
                }
                else
                {
                    mmsg->setSeq_Num(mmsg->getSeq_Num() + 1);
                }
                mmsg->setMycheckbits(parity);

                std::cout<<"sending sequence number "<<mmsg->getSeq_Num()<<endl;

                send(mmsg,"out");




}
