---
layout: post
title: "Systematics Normalization"
date: 2020-06-03
author: Abigail Wilson
---


# Systematics Normalization
I collaborated on this project with my mentors Emily Dolson and Kate Skocelas. 

## Goal: 
The purpose of this project is to develop a way to compare phylogenetic trees of different sizes and characteristics in a standardized way. 

#### Motivation: 
Within Empirical as it is now, there is not a good way to compare phylogenetic trees with one another. Different generational sizes and characteristics make it hard to obtain statistically significant data in terms of comparison. This project aims to solve this. 

#### Steps: 
 1. Creation of a **null model** of a phylogenetic tree 

 2. Creation of a tree that **mutates** and diverges in a non-random way
 3. Creation of a tree which accounts for **pressure for diversity** and **mutation**
 4. Comparing trees from steps 3 and 4 with our null model 

 -------------------------------------------

### **Systematics** 

Systematics.h is file manager in Empirical. It is used to track genotypes, species, clades, or lineages of organisms. Systematics allows a user to create phylogenetic trees with various levels of abstraction -- using genotypes, phenotypes, etc, to keep track of lineage. 

This project focused on two topics -- creating models to establish the possible range of phylogenetic diversity, then testing those models, and lastly, incorporating these percentiles into systematics so that a user could find out how their own trees compare. 

Within the systematics manager, I added two functions to use when calculating phylogenetic diversity. 

The first function, ```FindPhyloData()```, can be used if a user wants to compare results with the null model. It will calculate the phylogenetic diversity wherever the function is called and return the percentile corresponding to that value based on the data from the null model, which is stored in tree_percentiles.csv. 

**_in the final draft the included code will be simplified and commented more_**

```c++
  int FindPhyloData(){
    int percentile; 

    emp::File tree_percentiles("tree_percentiles.csv"); //loading file

    emp::vector< emp::vector<double> > percentile_data = tree_percentiles.ToData<double>(','); //turns data into an array

     int PhyloDiversity = GetPhylogeneticDiversity(); 

    for (int i = 0; i < percentile_data.size() - 1; i++){ 

        if( (PhyloDiversity >= percentile_data[i][1]) && (PhyloDiversity < percentile_data[i + 1][1])){ 
           std::cout << "Phylogenetic Diversity (recorded in systematics): " << PhyloDiversity << std::endl; 
           std::cout << "phylo diversity is in between: " << percentile_data[i][1] << " and " << percentile_data[i + 1][1] << std::endl; 
           std::cout << PhyloDiversity << " is in percentile: " << percentile_data[i][0] << std::endl;       

           percentile = percentile_data[i][0];

           std::cout << percentile << std::endl; 
           }
      }
      return percentile; 
    }
```

The following function is used for trees that contain pressure for diversity or mutations. It can also be used for multiple generations (10 through 100 gens). When called, it takes an argument of the number of generations. This corresponds to a line in OrgGenotypePercentiles.csv, each containing percentiles for different numbers of generations. This function only allows users to use multiples of 10 for the generation numbers though. For example, 10, 20, 30, ... 100 generations. 

_Right now, this function is used for testing our findings and prints the data to PercentileDataFullNoPressure.csv. This will probably be changed in the final product._

```c++
    void FindPhyloMultipleGens(int GenValueRaw){ 
      int GenValue = ((GenValueRaw / 10) - 1); 
      int percentile; 
      bool percentFound = false; 

        emp::File generation_percentiles("OrgGenotypePercentiles.csv");
        emp::vector< emp::vector<double> >percentile_data2 = generation_percentiles.ToData<double>(',');

      int PhyloDiversity = GetPhylogeneticDiversity(); 
      int lastval = size(percentile_data2[GenValue]) - 1; 
      std::cout << "Last element of array is: " << percentile_data2[GenValue][lastval] << std::endl;

      std::fstream fs; 
      fs.open("PercentileDataFullNoPressure.csv", std::fstream::in | std::fstream::out | std::fstream::app);

        //for(int i = 0; i < percentile_data2.size() - 1; i++){ 
          for(int j = 0; j <= percentile_data2[GenValue].size() - 2; j++){
          
          if((percentile_data2[GenValue][j] <= PhyloDiversity) && (percentile_data2[GenValue][j + 1] > PhyloDiversity)){
            std::cout << "phylo diversity is in between: " << percentile_data2[GenValue][j] << "and " << percentile_data2[GenValue][j+1] << std::endl;
            std::cout << "I is equal to: " << GenValue << std::endl; 
            std::cout << "J is equal to: " << j << std::endl;

            std::cout << "The Phylogentic diversity value " << PhyloDiversity << " is in the " << j << " percentile, in the " << ((GenValue + 1)* 10) << " generation" << std::endl;  

            fs << ((GenValue + 1)* 10) << "," << j << std::endl; 

            percentFound = true; 
          }
          
          if(PhyloDiversity >= percentile_data2[GenValue][lastval]){ 
              fs << ((GenValue + 1) * 10) << "," << 100 << std::endl; 
              fs.close(); 
            }

        if(percentFound == true){ 
            break; 
          }
          }
          if(percentFound == false){ 
            std::cout << "PHYLO DIVERSITY IS IN 100TH PERCENTILE" << std::endl; 
           }
        }
```

### **Phylogenetic Diversity**

We decided that I would use phylogenetic diversity as our metric for comparison. I could have also used evolutionary distinctiveness, however, phylogenetic diversity is a highly applicable trait among trees, and it is easy to calculate, making it a desirable metric for comparison. 

Within systematics and my models, phylogenetic diversity is defined as the number of internal nodes in the tree plus the number of extant taxa, minus one. This metric assumes that all branches from parent to child have a length of one. 

### **The Null Model**

A null model is a randomly generated model of an object or structure that is not constrained by its typical constraints, and is instead based on the randomization of data and structure, in an attempt to achieve the most unbiased model possible. 

Coming up with a null model of a tree was not the most intuitive, but we decided that having the most randomly generated model was the best option. 

We randomized how organisms were selected and how the tree branched as a result. 

The way that organisms were chosen for reproduction is shown here: 

```c++
int chooseOrg(vector<Organism> &currentGen, emp::Random &randNum){

    parentNum = randNum.GetInt(size(currentGen));  //chooses random spot 
    return parentNum;
}
```

Here the Empirical random number generator was utilized to ensure that results were actually random. Here, a random number was generated based on the size of the parent generation. That spot in the array was then set as the parent of the next generation. 

In the null model, each time a new organism was created it represented its own clade or taxon to ensure maximum diversity. 

### **Mutation and Pressure for Diversity** 

**Mutation**

The trees we used for comparison were trees with mutations and pressure for diversity. 

The mutation rate used for all of the trees was 0.05, which is a typical value for tree modeling. In these models, each organism had a genotype as an attribute. 

Mutation was determined randomly. The population generated in the first round of the tree all had a genotype of integer 0. A random double between 0 and 1 was generated with each creation of an organism following this generation. If the value generated was less than 0.05, the genotype would mutate. If a mutation was required, a new random number would be generate between -3 and 3. That genotype would then be subtracted from the original genotype. 

For example, if the organism had a genotype of 2, and was chosen to mutate, and the mutated genotype generated was -3, the new genotype for that organism would be 2 - (-3), which is 5. 

Mutations are also heritable, meaning that the child of an organism would inherit the same mutated or not mutated genotype as its parent. Once an organism mutated, it would create a branch in the tree. 

The following code shows how the organism class handles mutations. In the model that just used mutations but did not account for any pressure to diversify uses this organism class, but has no fitness calculations and still uses random choice for the creation of child organisms.  

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

**Pressure for Diversity**

In the model that used pressure for diversity and mutations, genotypes that were rarer were favored for reproduction over more common genotypes. When rarer genotypes are chosen, diversity increases throughout the tree. We referred to this as fitness which was calculated in the following code: 

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
```

**_THIS CODE NEEDS COMMENTING AND EXPLANATION_**

After fitness was calculated, the organisms with rarer fitness were chosen for reproduction. For this, I used the following ChooseOrgDiversity function. 

```c++
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

For example, I would set the number of generations in the null model to 10. Then, I would run it 1000 times, and at the end of each run, record the final diversity. I would then do 20 generations, and so forth, all the way through 100 generations. 

After that, I took that data and ran it through a python script which created a percentile range, by sorting all of the data from least to greatest. It would then take every 10th value in the dataset, to output 100 final diversity values, each corresponding to a percentile value from 0 to 100. For each of the different models, I repeated the same process.

To incorporate this data into the systematics manager, I imported the percentile csv files into the two functions described in the systematics section. Wherever these functions are called if future code, they will calculate the phylogenetic diversity of the tree and return the percentile value for how the tree compares to the models. 

After I had this framework setup I decided to test its reliability. I ran my models once again and had the systematics manager classify my diversity. I used the file containing percentiles for the tree that used mutations but had no pressure for diversity. The expected results of doing this should return values in the 50th percentile  most of the time if I run it with a tree with no pressure to diversify but having mutations. However, if I add pressure for diversity, those values should lie in the 100th percentile range. 


## **Results**

**The following table contains the percentile values for a tree with _no_ pressure for diversity**

|          |    |     |    |    |    |    |    |     |     |    | Standard Deviation | Average |
|----------|----|-----|----|----|----|----|----|-----|-----|----|--------------------|---------|
| 10 gens  | 37 |  80 | 61 | 61 | 80 | 80 | 61 |  37 |  80 | 37 |        18.76876838 |    61.4 |
| 20 gens  | 40 |  62 | 88 | 62 | 62 | 40 | 62 |  77 |  77 | 77 |        15.79767915 |    64.7 |
| 30 gens  | 87 |  97 | 75 | 36 | 75 | 16 | 75 |  16 |  75 | 57 |        28.76514094 |    60.9 |
| 40 gens  | 90 |  97 | 68 | 11 | 68 | 81 | 68 |  90 |  97 | 29 |        28.96914067 |    69.9 |
| 50 gens  | 74 |  86 | 39 | 39 | 97 | 86 | 39 | 100 |  93 |  6 |        32.48401316 |    65.9 |
| 60 gens  | 68 |  89 | 31 |  6 | 95 | 16 | 89 |  98 | 100 | 31 |        37.26198539 |    62.3 |
| 70 gens  | 86 | 100 | 76 | 26 | 86 | 42 | 76 |  93 | 100 | 76 |        24.25993496 |    76.1 |
| 80 gens  | 52 |  94 | 69 | 36 | 81 | 36 | 81 |  98 | 100 | 52 |         24.6371445 |    69.9 |
| 90 gens  | 47 |  86 | 98 | 17 | 86 | 17 | 86 |  61 |  96 | 47 |        30.97830782 |    64.1 |
| 100 gens | 39 |  81 | 70 | 12 | 89 | 39 | 70 |  70 |  89 | 89 |        26.28814689 |    64.8 |


**The table below contains the percentile values for a tree with pressure for diversity.**

|          |     |     |     |     |     |     |     |     |     |     | Standard Deviation | Average |
|----------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|--------------------|---------|
| 10 gens  |  96 |  80 |  90 |  61 |  98 |  90 |  80 |  96 |  13 |  90 |        25.78199199 |    79.4 |
| 20 gens  |  88 | 100 | 100 |  77 |  95 |  88 |  95 |  98 |  62 |  62 |        14.66856048 |    86.5 |
| 30 gens  |  75 |  75 |  97 | 100 |  97 |  75 |  95 |  98 |  95 |  87 |        10.50079362 |    89.4 |
| 40 gens  | 100 | 100 |  94 | 100 | 100 | 100 |  90 | 100 |  81 | 100 |        6.450667493 |    96.5 |
| 50 gens  | 100 |  97 |  93 | 100 | 100 |  97 | 100 | 100 |  97 | 100 |        2.366431913 |    98.4 |
| 60 gens  |  98 |  95 | 100 | 100 | 100 | 100 | 100 | 100 |  98 | 100 |        1.663329993 |    99.1 |
| 70 gens  | 100 | 100 |  97 | 100 | 100 | 100 | 100 | 100 | 100 | 100 |       0.9486832981 |    99.7 |
| 80 gens  | 100 | 100 |  94 | 100 | 100 |  98 |  94 |  98 | 100 | 100 |        2.458545189 |    98.4 |
| 90 gens  | 100 |  96 |  75 | 100 | 100 | 100 |  96 | 100 | 100 | 100 |        7.803845206 |    96.7 |
| 100 gens | 100 | 100 |  56 | 100 | 100 | 100 | 100 | 100 | 100 | 100 |         13.9140217 |    95.6 |

**NEXT STEPS**

Once I finalize my results next week I'll be able to add meaningful graphs and a conclusion section. 

**_In the graphs below, I have taken the average phylogenetic diversity achieved from each generation and plotted it over time (generations)._**

_The following graphs are more of a proof of concept than actual results and will be altered with the addition of new info. They do, however, show that phylogenetic diversity increases with more generations._

**Results from the Null Model**

![Graph](https://docs.google.com/spreadsheets/d/e/2PACX-1vSBPrXshSy5Dit31HWM6bmwbx0yWDu82Hz94AKyXjmBPxQWFqjf7yubgIOvAU9JCqO2Nzr4BFgjyjPD/pubchart?oid=346498229&format=image)

**Results from the model using mutations but no pressure for diversity**

![Graph 2](https://docs.google.com/spreadsheets/d/e/2PACX-1vQFSakq0kOodANU8RMiW4e3n5uL_nk3Zxo94GBWk4bqg8poVSMjLxYfMsGAKASOE9pAidTGyWxurR7s/pubchart?oid=841877077&format=image)

**Results from the model with mutations and pressure for diversity**

![Graph 3](https://docs.google.com/spreadsheets/d/e/2PACX-1vQS5lZwN6VlbDKRTm065_bZyIMHc-vlmjm3EF7TPtwL8DHo8eghiOE_ud6_Il99L7EFNpQ6cdjcKz6E/pubchart?oid=835426055&format=image)

## **Conclusion**

This workshop was an incredible learning experience for me. I am so grateful to my mentors, Emily and Kate, for their patience and guidance. I came into this workshop looking to improve my scientific computing and programming skills, and I can safely say that this workshop has provided me with a unique and invaluable way to do so. Thank you WAVES for such an incredible opportunity! 



