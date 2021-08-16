---
layout: post
title: "Systematics Normalization"
date: 2021-08-10
author: Abigail Wilson
---

# Systematics Normalization
I collaborated on this project with my mentor, Emily Dolson (www.emilyldolson.com). This project is part of [Empirical](https://github.com/devosoft/Empirical). This post will serve as a continuation of my post from last summer with some updated information. For more in depth information into earlier parts of this project and the details about the null model and diversity model, visit my blogpost from last summer here: http://mmore500.com/waves/blog/systematics-blogpost.html

### **Goal and Motivation:**

Phylogenetic tree analysis is a crucial tool for understanding evolutionary history. When measuring phylogenies of different sizes and shapes, it is important to have viable metrics that can be used for comparison. However, many phylogeny measurements are very sensitive to tree size. For example, phylogenetic diversity gets inflated as phylogenies get larger, making it difficult to meaningfully compare over time or between different populations. This problem is exacerbated in the context of digital evolution, where many assumptions about reconstructed phylogenies from nature are violated. It's unclear whether traditional approaches to normalizing phylogeny metrics remain valid in this new context. The optimal end result of this project, and ultimate motivation, is to provide computational and evolutionary biologists with tools that provide meaningful tree metrics. 

The aim of my work this summer has been to provide a continuation of the systematics normalization project I began last summer. The goal of this project has been to provide meaningful metrics for phylogenies of different sizes. Much of my work this summer to meet this goal involved testing previous findings against existing models, fleshing out previous experimentation, and formally recording these findings in a research paper.

### **The Short and Sweet**

The quick overview of my project can be summed up in the following. There is a random tree model which just creates randomly generated trees with whatever specifications for size and age you want. It creates these trees thousands of times and each time a tree is created, metrics about it are recorded and stored. After thousands of runs for trees of different sizes and ages, we look at that data and ask, what are the min and max values for this data and where does everything in between lie? We call this a percentile range. After that, we want to test this percentile range, so we run the model again with different random seeds and some other settings and make sure that they always average in the 50th percentile. Then, we make new models and test where those models fall in our percentile range and how those results fit into our other findings. Eventually, this allows us to confidently return to you both a value for your tree metric but also a percentile for that value. Aka, a useful metric for tree comparison. 

### **Background and Definitions:**

#### **Phylogenetic Trees**

A phylogenetic tree is a commonly used abstraction or way of thinking about evolutionary relationships in biology. Phylogenetic trees are used to show evolutionary relationships between organisms. The tree begins with a single group usually and branches when a portion of the population mutates. 

_This is a diagram of a basic phylogenetic tree. In this diagram, the population mutated 4 times (as shown by each divergence of the tree at each node). The final 5 taxa at the end of the tree each have unique genotypes and are considered distinct from one another._ 

![Phylo Tree Diagram]({{ site.baseurl }}/assets/abbywlsn/PhyloTreeDiagram.jpg)

#### **Phylogenetic Diversity**

Phylogenetic Diversity was used as the metric for tree comparison in this project for all of our models. Phylogenetic Diversity is a measure of biodiversity in a population or set of species. We have defined Phylogenetic Diversity as the number of ancestor taxa in a tree plus the number of active taxa minus one. This can be conceptualized as the number of edges in the minimum spanning tree, which happens to be the number of nodes minus one. This metric assumes that all branches from parent to child have a length of one. 

### **The Randomization Based Model**

The randomized model was primarily used for data collection in this project. This model used a randomization based approach for tree generation and produced metric values for the resulting trees. All of the metrics recorded from this model were used for normalization techniques. 

When we normalized the results from the null model during its second run, we found that the average was just around the 50th percentile, just as we expect that it would be. 

### **Adding and Comparing Pressure for Diversity**

Once data from the null model was collected and percentiles were generated, we tested a new type of tree against our normalization method. I added a pressure for the tree to diversify within the existing null model code. In this model, rarer genotypes are favored, which leads to more frequent branching and an overall more diverse tree. This tree produced results almost exclusively above the 90th percentile range. 

### **Exploring Other Models:**

A big part of the work I did this summer was trying to find new models to compare these findings to. There isn't a perfect existing model for this scenario (if there was, we wouldn't be creating one), but it was important to try affirm and question our findings. 

One model we looked at can be referred to as the complete distribution model. The complete distribution model would solve our problem of meaningful metrics by providing a glimpse at the entire tree permutation spectrum. With this approach, you would know the configuration and diversity of every tree with N leaf nodes, providing you with information on the true minimum and maximum values for diversity. 

This was a great model in theory and worked fantastically for smaller trees with fewer leaf nodes. However, major physical limitations arose when you wanted to look at trees with anything more than a few hundred leaf nodes. This limitation really just took us back to our original issue of being unable to compare trees across different sizes. 

Even with these computational limitations, we attempted to examine the findings for smaller trees and found another major drawback to this model. When generating this model, we had to assume that all possible trees were equally likely to exist and be generated during evolution. However, this is simply not reflective of the evolutionary process. For example, not all given taxa within a phylogeny will be alive at any given time point, particularly older taxa, which are more likely to have died off. Because of this, random trees with more leaf nodes towards the root of the tree are less favorable in an evolutionary simulation. The assumption that all of the possible trees would be equally favored produced skewed results that didn't reflect the experimental data. 

### **Future Improvements:**



