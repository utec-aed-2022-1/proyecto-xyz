//
// Created by Mauricio on 9/06/2022.
//

#ifndef PROYECTO_XYZ_BLOCKCHAIN_H
#define PROYECTO_XYZ_BLOCKCHAIN_H

class blockchain
{
private:
    using block = std::string;
    using TDATA = std::string;
    using THASH = std::string;
    using vector = Vector;

    vector<block> bc;

public:
    blockchain();
    blockchain(json data);

    bool serialize();
    bool deserialize();
    bool push(TDATA data);
    block front();
    block end();
    TDATA find(int position);
    bool edit(int position, TDATA data);
    bool clean();

    ~blockchain();
};

#endif // PROYECTO_XYZ_BLOCKCHAIN_H
