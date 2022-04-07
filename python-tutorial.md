# Python - NumPy

#### **SPOILER**: Python doesn't like iterative loops

*import numpy as np*

## ndarray
mulitdimensional array of homogeneous data (Tensor)
* ndim		: num dimensions (axes)
* shape		: tuple (num elements for each dimension)
* size		: num elements
* nbytes	: num bytes allocated
* dtype		: data type of elements

## Data Types:
* int8 int16 int32 int64
* uint8 uint16 uint32 uint64
* Bool
* float16 float32 float64 float128
* complex64 complex128 complex256

arr.astype( dtype ) : get a copy of arr with a different datatype

## Strides
defines the mapping of the elements in memory
a tuple of the same length as ndim, each value is the factor by which the index of the 
corresponding axes must be multiplied to obtain the correct index.

* shape: (3, 4), dtype: uint32, strides: (16, 4)	-> row major
* shape: (3, 4), dtype: uint32, strides: (4, 16)	-> col major

Views: a new ndarray is created but refers to the same data as the original array

## Creation of ndarrays
* np.array
* np.zeros
* np.ones
* np.diag
* np.linspace
* np.meshgrid
* np.loadtxt

## Accessing elements
Indexing: creates a **view**
* slices (m:n:s  from m to n-1 with stride s)
* positive integers (from 0 towards n-1)
* negative integers (from n-1 towards 0)

Fancy and Boolean indexing: creates a **copy**

## Reshaping an ndarray
* np.reshape:	creates a view
* np.flatten:	creates a copy
* np.ravel:		creates a view if possible, a copy otherwise
* np.squeeze:	removes axes with length 1
* np.expand_dims:	adds a new axis of length 1
* np.hstack:	stacks a list of arrays horizontally (axis 1)
* np.vstack:	stacks a list of arrays vertically (axis 0)
* np.concatenate:	general stacking
* np.resize:	creates a copy

----