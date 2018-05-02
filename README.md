# Pagerank-DOBFS
Direction-Optimizing Breadth-First Search (DOBFS) and Pagerank using Boost BGL and OPENMP


## Background
### Direction-Oprimizing Breadth-First Search
The algorithm proceeds step by step exploring the graph, in the case of top down step it populates the frontier adding all the nodes at distance + 1 from the current frontier.
In the case of  bottom up it search in the part of the graph that it’s still unexplored each node that is linked to a node of the frontier

The exchange between one algrithm for the computation of one step and the other is chosen by a finite state machine.The first step is always a Top-down step, then according to the magnitude of the branching factor the rule for the changing is the following:

𝑚_𝑓> |𝐺|/𝛼  𝑎𝑛𝑑 𝑏𝑓>0

Besides from Bottom up to Top-down:

𝑛_𝑓<|𝐺|/𝛽  𝑎𝑛𝑑 𝑏𝑓<0

where:
- 𝑚_𝑓: 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑒𝑑𝑔𝑒𝑠 𝑡𝑜 𝑐ℎ𝑒𝑐𝑘 𝑖𝑛 𝑡ℎ𝑒 𝑓𝑟𝑜𝑛𝑡𝑖𝑒𝑟 
- 𝑛_𝑓: 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑣𝑒𝑟𝑡𝑒𝑥 𝑖𝑛 𝑡ℎ𝑒 𝑓𝑟𝑜𝑛𝑡𝑖𝑒𝑟 
- |𝐺|: 𝑑𝑖𝑚𝑒𝑛𝑠𝑖𝑜𝑛 𝑜𝑓 𝑡ℎ𝑒 𝑔𝑟𝑎𝑝ℎ 
- 𝑏𝑓: 𝑏𝑟𝑎𝑛𝑐ℎ𝑖𝑛𝑔 𝑓𝑎𝑐𝑡𝑜𝑟 
- 𝛼: 𝑝𝑎𝑟𝑎𝑚𝑒𝑡𝑒𝑟 𝑜𝑓 𝑑𝑖𝑚𝑒𝑛𝑠𝑖𝑜𝑛 
- 𝛽: 𝑝𝑎𝑟𝑎𝑚𝑒𝑡𝑒𝑟 𝑜𝑓 𝑑𝑖𝑚𝑒𝑛𝑠𝑖𝑜𝑛 



### Pagerank
The algorithm of Pagerank is based on the following convergent series:

𝑃𝑅[𝑛𝑜𝑑𝑒]=(1−𝑑)/𝑁+𝑑∙(∑_k 𝑃𝑅[𝑛𝑜𝑑𝑒_𝑘]/𝐶[𝑛𝑜𝑑𝑒_𝑘] )

The algorithm is mainly composed by a cycle, executed until a maximum value or a convergence threshold are reached. 
However initially we set the values of node to a constant equal to one, and we save, for each node, the number of outgoing edges.
At the beginning of the cycle the pagerank values are copied into a vector called memory, and the values of the pagerank into the graph are set to zero.

Then in a inner cycle, for each node of the graph, we compute an update value of the node, as:

𝑢𝑝𝑑𝑎𝑡𝑒=[((𝑑𝑎𝑚𝑝𝑖𝑛𝑔 𝑓𝑎𝑐𝑡𝑜𝑟 ∗ 𝑚𝑒𝑚𝑜𝑟𝑦[𝑛𝑜𝑑𝑒]))/(𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑜𝑢𝑡𝑔𝑜𝑖𝑛𝑔 𝑒𝑑𝑔𝑒𝑠)]

Then we sum the update to the pagerank value of the connected nodes.
After the computation of the update value, we add in the i-th node PR the bias. So, we get a convergent serie.
The error is the last thing computed in the main cylce, with the formula:

𝑒𝑟𝑟𝑜𝑟=∑_k |𝑃𝑅(𝑛𝑜𝑑𝑒_𝑘 )−𝑚𝑒𝑚𝑜𝑟𝑦_𝑘 |

## MAKEFILE
To make the project it's possible to choose between three commands
```
make all
```
```
make algorithms
```
```
make test
```


## Additional Argument
### Algorithms
To output the available additional arguments
```
./algorithms -h
```

```
Additional Arguments:
		 *input file (default: out.dot). E.g., -i INfile.dot
		 *output file (default: result.dot). E.g., -o OUTfile.dot
		 *initial ID vertex for BFS (default 0). E.g., -id 9
		 *Sequential BFS (default true). E.g., -noSequentialBFS
		 *Parallel BFS (default true). E.g., -noParallelBFS
		 *Pagerank (default true). E.g., -noPagerank
		 *Fixed Pagerank (default true). E.g., -noFixedPagerank
		 *Alpha parameter DOBFS (default 12). E.g., -alpha
		 *Beta Parameter DOBFS (default 24). E.g., -beta
		 *Pagerank Damping Factor (default 0.85). E.g., -df 0.9
		 *Pagerank Iteration (default 100). E.g., -iter 
```

### Test
To output the available additional arguments
```
./test -h
```

```
Additional Arguments:
		 *input file (default: out.dot). E.g., -i INfile.dot
		 *output file (default: test_log.txt). E.g., -o testPagerank.txt
		 *initial ID vertex for BFS (default 0). E.g., -id 9
		 *Test BFS (default true). E.g., -noTestBFS
		 *Test Pagerank (default true). E.g., -noTestPagerank
		 *Pagerank Iteration (default 100). E.g., -iter 
```
