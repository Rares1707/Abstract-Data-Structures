# Abstract-Data-Structures

## Overview
These are the Abstract Data Types (ADTs) that I implemented as part of my university's Data Structures and Algorithms module:
- **Set** - represented as a dynamic array of Boolean values. For example the set {5, 1, -4, 0, 8} can be represented as an array of 13 elements where position 0 corresponds to element 4, position 1 corresponds to element -3, …, position 12 corresponds to element 8: [true, false, false, false, true, true, false, false, false, true, false, false, true].
- **SortedSet** – using a DLL where elements are ordered based on a relation between the elements.
- **ADT SortedMultiMap** – using a DLLA with (key, value) pairs ordered based on a relation on the keys. A key can appear in multiple pairs.

**Note: C++'s STL was avoided because the aim of these projects was to implement the ADT's by myself and obtain a clear understanding .**

## Features
- they are as optimized as I could make them
- the code specifies the time complexities of operations such as adding, removing, resizing, etc.
- they include iterators where applicable
- they include comprehensive tests for thorough evaluation provided by the module's coordinator teacher

  
## Technologies used
- C++
