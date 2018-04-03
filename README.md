# Rspackage
Rspackage is a simple, easy-using developing software/library for Recommender System to train and predict. 

More features and algorithms will be added soon.

## Table of Cotents

- Installation and Data Format
- Algorithms
- Usage
- Examples
- Eigen Version
- Further development

## Installation and Data Format

On Unix-like system, type `make` to build main(sample program).

On other systems, Visiual Stdio/Xcode can directly build the project on Rspackage.

The format of training validation and testing data file is:

```<user>  <rating>  <time>```

## Algorithms

- Matrix Factorizaion
- Item-based KNN
- Neural network blending

###Matrix Factorization
$$ \hat{r}_{u,i}=\bar{r}+b_u^{user}+b_i^{item}+\rm{p_u}^T\rm{q_i}$$

### Item-based KNN

$$ \hat{r}\_{u,i}=\frac{\sum\_{j\in G_k(u,i)} w\_{ij}\cdot r\_{uj}}{\sum\_{j\in G_k(u,i)} w\_{ij}}  $$

### Neural network
Comming soon...

## Usage

The sample program named main.cc is shown below:

```
#include "algorithms/basicMF.h"
#include "algorithms/basicKNN.h"
#include "algorithms/matrix/basicMF_m.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	basicSolver* s=new basicKNN("ua.base");
	//Read the training set
	s->Init();
	//Train with validation set of none
	s->train("validation dataset");
	//Predict
	cout<<"Predict error:"<<s->predict("ua.test")<<endl;
	delete s;
	return 0;
}
```

Class basicMF provides basic Matrix Factorization function. The train set and the number of features are initialized by Constructor.

Class basicKNN provides the item-based KNN algorithm.

## Examples
__Result on Movielens-100k__

Algorithms   | MAE           | RMSE
------------ | ------------- | ------------
basicMF      | 0.738367      | 0.935906 
basicKNN     | 0.772263      | 0.981548 

More datasets will be tested.

##Eigen Version
Rspackage involves a lot of matrix operations, so it provides a matrix version.

[**Eigen is a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.**](http://eigen.tuxfamily.org/index.php?title=Main_Page)

The solver basicMF_m is implemented with Eigen library, it looks pretty but is a little time consuming than original version, but it still runs faster than matlab and python.

## Further Development

Now I am ready to add blending techniques and RBM methods into Rspackage, which is common in competitions. 

Rspackage is easy to extend. The class rating and basicSolver is basis of complex individous model, and people can easily write their own solver.

