---
layout: post
title: "Systematics Normalization"
date: 2021-08-10
author: Abigail Wilson
---

# Systematics Normalization
I collaborated on this project with my mentor, Emily Dolson (www.emilyldolson.com). This project is part of [Empirical](https://github.com/devosoft/Empirical). This post will serve as a continuation of my post from last summer with some updated information. For more in depth information into earlier parts of this project and the details about the null model and diversity model, visit my blogpost from last summer here: http://mmore500.com/waves/blog/systematics-blogpost.html

F
### **Goal:**
The aim of my work this summer was to provide a continuation of the systematics normalization project I began last summer. This meant testing previous findings against existing models, fleshing out previous experimentation, and formally recording these findings in a research paper. 

### **Background and Motivation:**

Phylogenetic tree analysis is a crucial tool for understanding evolutionary history. When measuring phylogenies of different sizes and shapes, it is important to have viable metrics that can be used for comparison. However, many phylogeny measurements are very sensitive to tree size. For example, phylogenetic diversity gets inflated as phylogenies get larger, making it difficult to meaningfully compare over time or between different populations. This problem is exacerbated in the context of digital evolution, where many assumptions about reconstructed phylogenies from nature are violated. It's unclear whether traditional approaches to normalizing phylogeny metrics remain valid in this new context. The optimal end result of this project, and ultimate motivation, is to provide computational and evolutionary biologists with tools that provide meaningful tree metrics. 

### **The Short and Sweet Version**

The quick overview of my project goes as follows. There is a random tree model which just creates randomly generated trees with whatever specifications for size and age you want. It creates these trees thousands of times and each time a tree is created, metrics about it are recorded and stored. After thousands of runs for trees of different sizes and ages, we look at that data and ask, what are the min and max values for this data and where does everything in between lie? We call this a percentile range. After that, we want to test this percentile range, so we run the model again with different random seeds and what not. We make sure they always average in the 50th percentile. Then, we make new models and test where those models fall in our percentile range. Eventually, this allows us to confidently return to you both a value for your tree metric but also a percentile for that value. Aka, a useful metric for tree comparison. 

### **Background and Definitions:**

#### **Phylogenetic Trees**

A phylogenetic tree is a commonly used abstraction or way of thinking about evolutionary relationships in biology. Phylogenetic trees are used to show evolutionary relationships between organisms. The tree begins with a single group usually and branches when a portion of the population mutates. 

_This is a diagram of a basic phylogenetic tree. In this diagram, the population mutated 4 times (as shown by each divergence of the tree at each node). The final 5 taxa at the end of the tree each have unique genotypes and are considered distinct from one another._ 

![Phylo Tree Diagram]({{ site.baseurl }}/assets/abbywlsn/PhyloTreeDiagram.jpg)

#### **Phylogenetic Diversity**

Phylogenetic Diversity was used as the metric for tree comparison in this project for all of our models. Phylogenetic Diversity is a measure of biodiversity in a population or set of species. We have defined Phylogenetic Diversity as the number of ancestor taxa in a tree plus the number of active taxa minus one. This can be conceptualized as the number of edges in the minimum spanning tree, which happens to be the number of nodes minus one. This metric assumes that all branches from parent to child have a length of one. 

### **The Null Model**


### **Adding and Comparing Pressure for Diversity**


### **Exploring Other Models:**



### **Imporvements:** 

### **Initial Findings:**

### **Future Improvements:**



