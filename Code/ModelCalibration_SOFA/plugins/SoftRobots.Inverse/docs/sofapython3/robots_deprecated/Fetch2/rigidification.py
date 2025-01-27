
# utility methods for rigidification

# We suppose that we have a mesh with a given number of nodes
# - a subpart of these nodes are 'free'
# - the remaining part of these nodes are grouped in 'rigidified' blocks

# for the mapping, we need to build a list of index pairs, 1 pair / nodes
# [ [model Origin (free = 0, rigidified = 1 to n)   number in the subpart list]

# see the exemple described in the test for a better understanding...




def fillIndexPairs(numNodes, freeNodes, rigidBlocks):
    numRigidBlocks = len(rigidBlocks)

    
    
    # TODO verify that the lists of freeNodes and rigidBlocks are provided in ascending order !
    iteratorFreeNodes=0;
    iteratorRigidBlocks=[0]*numRigidBlocks
    
    #  iterators limits
    numFreeNodes = len(freeNodes);
    numRigidNodesOnBlock = [0]*numRigidBlocks

    
    for j in range (numRigidBlocks):
        numRigidNodesOnBlock[j] =  len(rigidBlocks[j])
    
    # test num Nodes:
    numNodes2 = numFreeNodes+sum(numRigidNodesOnBlock)
    print 'numNodes2 :' +str(numNodes2)

    if numNodes != numNodes2:
        print '+++++++++++++++++++++++++++++++++++++++++++++'
        print 'error in the lists freeNodes and rigidBlocks'
        print '+++++++++++++++++++++++++++++++++++++++++++++'
        print 'numNodes = '+ str(numNodes)+ ' does not corresponds to total size of freeNodes + rigidBlocks'
        print 'freeNodes: size ='+ str(numFreeNodes)
        print 'rigidBlocks: size = '+ str(sum(numRigidNodesOnBlock))
        print '+++++++++++++++++++++++++++++++++++++++++++++'
        return [ ]
    
    
    #result:
    indexPairs=[1,1]*(numNodes)
    
    for i in range(numNodes):
    
        if i==freeNodes[iteratorFreeNodes]:
            # node i belongs to free Nodes
            indexPairs[2*i  ]=0;
            indexPairs[2*i+1]=iteratorFreeNodes;
            iteratorFreeNodes=iteratorFreeNodes+1;
            
            if (iteratorFreeNodes>=numFreeNodes): # we are at the limit
                iteratorFreeNodes = iteratorFreeNodes-1;
        
                
        else:
            for j in range (numRigidBlocks):
                if i==rigidBlocks[j][iteratorRigidBlocks[j]]:
                    indexPairs[2*i  ]=j+1;
                    indexPairs[2*i+1]=iteratorRigidBlocks[j];
                    iteratorRigidBlocks[j] = iteratorRigidBlocks[j]+1;

                    if (iteratorRigidBlocks[j]>=numRigidNodesOnBlock[j]): # we are at the limit of the node list
                        iteratorRigidBlocks[j] = iteratorRigidBlocks[j]-1;
                            

    return indexPairs

def doTest():
    # example TEST
    # lets consider that we have a mesh with 10 nodes
    # free: nodes 0 2 3 4 6
    # 1st rigid block: nodes 1 7 9
    # 2d rigid block: nodes 5 8

    # the function should provide:
    # free nodes: [0 0] [0 1] [0 2] [0 3] [0 4]
    # 1st rigid block: nodes [1 0] [1 1] [1 2]
    # 2d rigid block: nodes [2 0] [2 1]

    # the method should provide the following pairs
    # [[0 0] [1 0] [0 1] [0 2] [0 3] [2 0] [0 4] [1 1] [2 1] [1 2]]
    # and the mapping of SOFA requires a simple list:
    # [0,0,1,0,0,1,0,2,0,3,2,0,0,4,1,1,2,1,1,2]

    freeNodes=[0, 2, 3, 4, 6];
    rigidBlocks=[[1,7,9], [5,8]];
    numNodes=12;
    
    
    index_result = fillIndexPairs(numNodes, freeNodes, rigidBlocks);
    print 'result='
    print index_result
    
    if [0,0,1,0,0,1,0,2,0,3,2,0,0,4,1,1,2,1,1,2] == index_result:
        print ('result ok')
    else:
        print ('error')

    return



if __name__ == '__main__':
    doTest()














