# Pagerank-DOBFS
Direction-Optimizing Breadth-First Search (DOBFS) and Pagerank using Boost BGL and OPENMP


## BackGround

## MAKEFILE

## Additional Argument
### Algorithms
To output the available additional argument
```
./algorithms -h
```

```
Additional Argument:
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
```
./test -h
```

```
Additional Argument:
		 *input file (default: out.dot). E.g., -i INfile.dot
		 *output file (default: test_log.txt). E.g., -o OUTfile.dot
		 *initial ID vertex for BFS (default 0). E.g., -id 9
		 *Test BFS (default true). E.g., -noTestBFS
		 *Test Pagerank (default true). E.g., -noTestPagerank
		 *Pagerank Iteration (default 100). E.g., -iter 
```
