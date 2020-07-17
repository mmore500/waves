---
layout: post
title: "Systematics Project"
date: 2020-06-03
author: Abigail Wilson
---


# Systematics Normalization

#### Goal: 
The purpose of this project is to develop a way to compare phylogenetic trees of different sizes and characteristics in a standardized way. 

#### Motivation: 
Within Empirical as it is now, there is not a good way to compare phylogenetic trees with one another. Different generational sizes and characteristics make it hard to obtain statistically significant data in terms of comparison. This project aims to solve this. 

#### Steps: 
 1. Creation of a **null model** of a phylogentic tree 

 2. Creation of a tree that **mutates** and diverges in a non-random way
 3. Creation of a tree which accounts for **pressure for diversity** and **mutation**
 4. Comparing trees from steps 3 and 4 with our null model 

## **Systematics** 

Systematics is used in Empirical as a way to ...

### **Phylogenetic Diversity**

We decided that I would use Phylogenetic Diversity as our metric for comparison. Phylogenetic Diversity is a highly applicable trait among trees, and is easy to calculate, making it a desirable metric. 

Within systematics and my models, Phylogenetic Diversity is defined as the number of internal nodes in the tree plus the number of extant taxa, minus one. This metric assumes that all branches from parent to child have a length of one. 

### **The Null Model**
Coming up with a null model of a tree was not the most intuitive, but we decided that having the most randomly generated model was the best option. 

The way that organisms were chosen for reproduction is shown here: 

```
int chooseOrg(vector<Organism> &currentGen, emp::Random &randNum){

    parentNum = randNum.GetInt(10);  //chooses random spot in array for parent
    //cout << "parent chosen is in spot " << parentNum << " in currentGen array which is " << size(currentGen) << " long" << endl;
    return parentNum;
}
```

Here the Empirical number generator was utilized to ensure that results were actually random. 

### **Mutation and Pressure for Diversity** 
The trees we used for comparison were trees with mutations and a pressure for diversity. 

* Mutation rate used was 0.05
* random number was generated between 0 and 1, if the number was less than 0.05, the organism's genotype (simple integer) would mutate and the child of that organism would inherit the mutated genotype, branching the tree

![Graph](https://docs.google.com/spreadsheets/d/e/2PACX-1vSBPrXshSy5Dit31HWM6bmwbx0yWDu82Hz94AKyXjmBPxQWFqjf7yubgIOvAU9JCqO2Nzr4BFgjyjPD/pubchart?oid=1072178104&format=image)

![Graph 2](https://docs.google.com/spreadsheets/d/e/2PACX-1vQFSakq0kOodANU8RMiW4e3n5uL_nk3Zxo94GBWk4bqg8poVSMjLxYfMsGAKASOE9pAidTGyWxurR7s/pubchart?oid=1960655507&format=image)

![Graph 3](https://docs.google.com/spreadsheets/d/e/2PACX-1vQS5lZwN6VlbDKRTm065_bZyIMHc-vlmjm3EF7TPtwL8DHo8eghiOE_ud6_Il99L7EFNpQ6cdjcKz6E/pubchart?oid=1440303338&format=image)
