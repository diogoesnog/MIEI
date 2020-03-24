#!/usr/bin/env python3

import hashlib as hasher
import datetime as date


class Block:
    '''
    Single block in a blockchain
    '''
    def __init__(self, index, timestamp, data, previous_hash):
        self.index = index
        self.timestamp = timestamp
        self.data = data
        self.previous_hash = previous_hash
        self.hash = self.hash_block()

    def hash_block(self):
        sha = hasher.sha256()
        sha.update((str(self.index)+str(self.timestamp)+self.data+self.previous_hash).encode())
        return sha.hexdigest()

class Blockchain:
    def __init__(self):
        self.chain = [self.create_genesis_block()]

    def create_genesis_block(self):
        return Block(0, date.datetime.now(), "Genesis Block", "0")

    def next_block(self):
        block_index = len(self.chain)
        last_block = self.chain[block_index-1]
        return Block(block_index, date.datetime.now(), "BlockIndex:"+str(block_index), last_block.hash)
    
    def add_block(self, block):
        self.chain.append(block)

def main():
    bc = Blockchain()

    for i in range(0,20):
        n_block = bc.next_block()
        bc.add_block(n_block)
        print("Block #{} has been added to the blockchain!".format(n_block.index))
        print("Hash: {}\n".format(n_block.hash))


if __name__ == "__main__":
    main()
