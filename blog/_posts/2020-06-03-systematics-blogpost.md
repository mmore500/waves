---
layout: post
title: "Systematics Project"
date: 2020-06-03
author: Abigail Wilson
---


# Systematics Normalization

## Goal: 
The purpose of this project is to develop a way to compare phylogenetic trees of different sizes and characteristics in a standardized way. 

#### Motivation: 
Within Empirical as it is now, there is not a good way to compare phylogenetic trees with one another. Different generational sizes and characteristics make it hard to obtain statistically significant data in terms of comparison. This project aims to solve this. 

#### Steps: 
 1. Creation of a **null model** of a phylogentic tree 

 2. Creation of a tree that **mutates** and diverges in a non-random way
 3. Creation of a tree which accounts for **pressure for diversity** and **mutation**
 4. Comparing trees from steps 3 and 4 with our null model 

 -------------------------------------------

### **Systematics** 

Systematics is used in Empirical as a way to ...
* Will mainly incorporate details from the documentation I wrote for systematics 

### **Phylogenetic Diversity**

We decided that I would use Phylogenetic Diversity as our metric for comparison. Phylogenetic Diversity is a highly applicable trait among trees, and is easy to calculate, making it a desirable metric. 

Within systematics and my models, Phylogenetic Diversity is defined as the number of internal nodes in the tree plus the number of extant taxa, minus one. This metric assumes that all branches from parent to child have a length of one. 

### **The Null Model**
Coming up with a null model of a tree was not the most intuitive, but we decided that having the most randomly generated model was the best option. 

The way that organisms were chosen for reproduction is shown here: 

```c++
int chooseOrg(vector<Organism> &currentGen, emp::Random &randNum){

    parentNum = randNum.GetInt(10);  //chooses random spot in array
    return parentNum;
}
```

Here the Empirical number generator was utilized to ensure that results were actually random. 

* Each new organism was its own clade or taxon
    * allowed for maximum diversity 

### **Mutation and Pressure for Diversity** 
The trees we used for comparison were trees with mutations and a pressure for diversity. 

* Mutation rate used was 0.05
* random number was generated between 0 and 1, if the number was less than 0.05, the organism's genotype (simple integer) would mutate and the child of that organism would inherit the mutated genotype, branching the tree

**Pressure for Diversity**

* rarer genotypes are favored for reproduction, increasing diversity

**Organism Class**

Each time an organism is created, it will either develop a mutation and have a new genotype, or develop no mutation and keep its previous genotype. 

```c++
class Organism {
public:
    int genotype = 0;

    Organism() {
    }

    Organism(int _genotype) {
        genotype = _genotype;
    }

    int MutateGenotype(emp::Random &RandNum) {

        double randMutation = RandNum.GetDouble(0, 1);

        if (randMutation < mutRate) {
            int MutatedGenotype = genotype - RandNum.GetInt(-3, 3);
            genotype = MutatedGenotype;
            cout << "mutated genotype = " << genotype << endl;
        } else {
            cout << "not mutated genotype = " << genotype << endl;
        }

        return genotype;
    }
};
```

The model with mutation but no pressure for diversity implements this code but uses the same ChooseOrg function as shown for the null model.  

### **Pressure for Diversity and Mutations**

**_THIS CODE NEEDS COMMENTING AND EXPLANATION_**

```c++
void calcFitness(vector<Organism> &currentGen, vector<double> &fitnessVect, emp::Random &randNum) {
    fitnessVect.resize(0);

    vector<int> fitnessCalc;

    fitnessCalc.reserve(currentGen.size());
    for (int i = 0; i < currentGen.size(); i++) {
        fitnessCalc.push_back(currentGen[i].genotype);
    }

    map<int, int> CountMap;

    for (int j = 0; j < fitnessCalc.size(); j++) {
        if (emp::Has(CountMap, fitnessCalc[j])) {
            CountMap[fitnessCalc[j]]++;
        } else {
            CountMap[fitnessCalc[j]] = 1;

        }
    }

    for(int k = 0; k < fitnessCalc.size(); k++){
        fitnessVect.push_back(1.0/CountMap[fitnessCalc[k]]);
    }
}


int chooseOrgDiversity(vector<double> &fitnessVect, emp::Random &randNum){
    emp::IndexMap fitness_index(fitnessVect.size());

    for (size_t id = 0; id < fitnessVect.size(); id++){
        fitness_index.Adjust(id, fitnessVect[id]);
    }

    const double fit_pos = randNum.GetDouble(fitness_index.GetWeight());
    size_t parent_id = fitness_index.Index(fit_pos);

    //cout << "FITNESS VECTOR VALUES: " << endl;

    for(int pos = 0; pos < fitnessVect.size(); pos++){
        //cout << fitnessVect[pos] << " " << endl;
    }

    parentNum = parent_id;

    cout << "PARENT NUM AFTER CHOOSEORGDIVERSITY: " << parentNum << endl;
    cout << "fitness val at parent_id: " << fitnessVect[parent_id] << endl;

    return parentNum;
}
```


------------------------- 

## **Method**

With each of the three models, I ran each one 1000 times for every 10 generations and collected the Phylogenetic Diversity values at the end of each run.

For example, I would set the number of generations in the null model to be 10. Then, I would run it 1000 times, and at the end of each run, record the final diversity. I would then do 20 generations, and so forth, all the way through 100 generations. 

After that, I took that data and ran it through a python script which created a percentile range, by sorting all of the data from least to greatest. It would then take every 10th value in the dataset, to output 100 final diversity values, each corresponding to a percentile value from 0 to 100. For each of the different models, I repeated the same process.

**NEXT STEPS**
* Using models and percentiles to determine if this can actually be used to tell a user where their phylogenetic diversity values actually fall in comparison
* Incorporation into systematics 

**_In the graphs below, I have taken the highest Phylogenetic Diversity achieved from each generation and plotted it over time (generations)._**

## **RESULTS**

_The following graphs are more of a proof of concept than actual results and will be altered with the addition of new info._

**Results from the Null Model**

![Graph](https://docs.google.com/spreadsheets/d/e/2PACX-1vSBPrXshSy5Dit31HWM6bmwbx0yWDu82Hz94AKyXjmBPxQWFqjf7yubgIOvAU9JCqO2Nzr4BFgjyjPD/pubchart?oid=346498229&format=image)

**Results from the model using mutations but no pressure for diversity**

![Graph 2](https://docs.google.com/spreadsheets/d/e/2PACX-1vQFSakq0kOodANU8RMiW4e3n5uL_nk3Zxo94GBWk4bqg8poVSMjLxYfMsGAKASOE9pAidTGyWxurR7s/pubchart?oid=841877077&format=image)

**Results from the model with mutations and pressure for diversity**

![Graph 3](https://docs.google.com/spreadsheets/d/e/2PACX-1vQS5lZwN6VlbDKRTm065_bZyIMHc-vlmjm3EF7TPtwL8DHo8eghiOE_ud6_Il99L7EFNpQ6cdjcKz6E/pubchart?oid=835426055&format=image)



