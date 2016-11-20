# genetic-algorithms-tutorial
This repository includes project for genetic algorithms consisting of given problem: 

##Problem Definition

 Given the digits 0 through 9 and the operators +, -, * and /,  find a sequence that will represent a given target number. The operators will be applied sequentially from left to right as you read.

 

So, given the target number 23, the sequence 6+5*4/2+1 would be one possible solution.
If  75.5 is the chosen number then 5/2+9*7-5 would be a possible solution. 

 

           
 
##Stage 1: Encoding

 

First we need to encode a possible solution as a string of bits… a chromosome. So how do we do this? Well, first we need to represent all the different characters available to the solution... that is 0 through 9 and +, -, * and /. This will represent a gene. Each chromosome will be made up of several genes.

 

Four bits are required to represent the range of characters used:

 

0:         0000

1:         0001

2:         0010

3:         0011

4:         0100

5:         0101

6:         0110

7:         0111

8:         1000

9:         1001

+:         1010

-:          1011

*:          1100

/:          1101

 

The above show all the different genes required to encode the problem as described. The possible genes 1110 & 1111 will remain unused and will be ignored by the algorithm if encountered.

 

So now you can see that the solution mentioned above for 23, ' 6+5*4/2+1' would be represented by nine genes like so:

 

0110 1010 0101 1100 0100 1101 0010 1010 0001

 

6        +        5        *        4         /        2        +       1

 

These genes are all strung together to form the chromosome:

 

 011010100101110001001101001010100001

 

###A Quick Word about Decoding

 

Because the algorithm deals with random arrangements of bits it is often going to come across a string of bits like this:

 

0010001010101110101101110010

 

Decoded, these bits represent:

 

0010 0010 1010 1110 1011 0111 0010

 

2        2        +        n/a     -        7        2

 

Which is meaningless in the context of this problem! Therefore, when decoding, the algorithm will just ignore any genes which don’t conform to the expected pattern of: number -> operator -> number -> operator …and so on. With this in mind the above ‘nonsense’ chromosome is read (and tested) as:

 

2   +   7

###Reference
Details of tutorial can be found in here:
http://www.ai-junkie.com/ga/intro/gat3.html

