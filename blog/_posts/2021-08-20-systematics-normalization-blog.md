---
layout: post
title: "Systematics Normalization"
date: 2021-08-20
author: Abigail Wilson
---

I collaborated on this project with my mentor, [Emily Dolson](www.emilyldolson.com). This project is part of [Empirical](https://github.com/devosoft/Empirical). This post will serve as a continuation of my post from last summer with some updated information. For more in depth information into earlier parts of this project and details about the randomization based approach, visit my blogpost from last summer [here]({{ site.base_url }}/blog/systematics-blogpost.html).

# Goal and Motivation

Phylogenetic tree analysis is a crucial tool for understanding evolutionary history. When measuring phylogenies of different ages, it is important to have viable metrics that can be used for comparison. However, many phylogeny measurements are sensitive to tree age. For example, phylogenetic diversity gets inflated as phylogenies get larger, making it difficult to meaningfully compare over time or between different populations. This problem is exacerbated in the context of digital evolution, where many assumptions about reconstructed phylogenies from nature are violated. It's unclear whether traditional approaches to normalizing phylogeny metrics remain valid in this new context. The optimal end result of this project, and ultimate motivation, is to provide computational and evolutionary biologists with tools that provide meaningful tree metrics.

The aim of my work this summer has been to provide a continuation of the systematics normalization project I began last summer. The goal of this project is to provide meaningful metrics for phylogenies of different sizes. Much of my work this summer to meet this goal involved testing previous findings against existing models, fleshing out previous experimentation, and formally recording these findings in a research paper.

# The Short and Sweet

The quick overview of my project can be summed up in the following. There is a random tree model which just creates randomly generated trees with whatever specifications for size and age you want. It creates these trees thousands of times and each time a tree is created, metrics about it are recorded and stored. After thousands of runs for trees of different sizes and ages, we look at that data and ask, what are the min and max values for this data and where does everything in between lie? We call this a percentile range. After that, we want to test this percentile range, so we run the model again with different random seeds and some other settings and analyze the results. Then, we make new models and test where those models fall in our percentile range and how those results fit into our other findings. Eventually, this allows us to confidently return to you both a value for your tree metric but also a percentile for that value. Aka, a useful metric for tree comparison.

# Background and Definitions

## Phylogenetic Trees

A phylogenetic tree is a commonly used abstraction or way of thinking about evolutionary relationships in biology. Phylogenetic trees are used to show evolutionary relationships between populations or taxa. The tree begins with a single group usually and branches when a portion of the population mutates.

## Phylogenetic Diversity

Phylogenetic Diversity was used as the metric for tree comparison in this project for all of our models. Phylogenetic Diversity is a measure of biodiversity in a population or set of species. Phylogenetic Diversity is defined as the number of ancestor taxa in a tree plus the number of active taxa minus one. This can be conceptualized as the number of edges in the minimum spanning tree (a computer science term that basically means the smallest possible sum of edges that still span the tree), which happens to be the number of nodes minus one. This metric assumes that all branches from parent to child have a length of one.

# The Randomization Based Model

The randomized model was primarily used for data collection in this project. This model used a randomization based approach for tree generation and produced metric values for the resulting trees. This model displayed no environmental pressures or limitations. It simply chose randomly if a population would mutate or not. These randomly generated trees were created thousands of times. More specifically, data was collected for trees with 1 through 1000 generations and for differently sized populations of 10, 100, and 1000 organisms per generation.

The big idea here is that With enough data collection, this model should produce a large range of possible tree permutations.  This range should include or get close to the smallest and largest possible metric values and provide a representative sample of the values in between for each different type of tree.

Once this data was collected, it was turned into a percentile range.

We then tested the same model against these newly created percentile ranges, in hopes of seeing an average around the 50th percentile with data spanning the range of possible values. This would be expected as we changed nothing about the way our model was running other than the random seeds being used. Both of these expectations held  true during experimentation.

# Adding and Comparing Pressure for Diversity

Once data from the null model was collected and percentiles were generated, we tested a new type of tree against our normalization method. I added a pressure for the tree to diversify within the existing null model code. We added an extreme form of pressure to the tree in the form of organism fitness that we hoped would return very high percentile values. In this model, rarer genotypes are favored, which should lead to more frequent branching and an overall more diverse tree when implemented. This tree produced results almost exclusively above the 90th percentile range, many in the 100th percentile.

# Exploring Other Models

A big part of the work I did this summer was trying to find new models to compare these findings to. There isn't a perfect existing model for this scenario (if there was, we wouldn't be creating one), but it was important to try to affirm and question our findings as well as look for more successful approaches.

One model we looked at can be referred to as a uniform model. The model would solve our problem of meaningful metrics by providing a glimpse at the entire tree permutation spectrum. With this approach, you would know the configuration and phylogenetic diversity of every tree with N leaf nodes, providing you with information on the true minimum and maximum values for diversity and everything in between.

This was a great model in theory and initially seemed to work fantastically for smaller trees with fewer leaf nodes. However, major physical limitations arose when you wanted to look at trees with anything more than a few hundred leaf nodes. This limitation really just took us back to our original issue of being unable to compare trees across different sizes.

Even with these computational limitations, we attempted to examine the findings for smaller trees and found another major drawback to this model. When generating this model, we had to assume that all possible trees were equally likely to exist and be generated during evolution. However, this is simply not reflective of the evolutionary process. For example, not all given taxa within a phylogeny will be alive at any given time point, particularly older taxa, which are more likely to have died off. Because of this, random trees with more leaf nodes towards the root of the tree are less favorable in an evolutionary simulation. The assumption that all of the possible trees would be equally favored produced skewed results that didn't reflect the experimental data.

# Future Improvements

While I have been working on this project for two summers, there is still a significant amount of work to be done.

I would like to add a wider variety of models to test our percentile ranges. Especially, it will be important to have more models in the middle ground (like the 70th percentile). It will also be useful to flesh out the tails of these percentile ranges and account for values in the extremes. Eventually, we also plan to explore the traditional Yule Model approach to solving this problem and compare our solution to those results. Lastly, incorporating more metrics outside of Phylogenetic Diversity will be vital for the success of this endeavor.

# Acknowledgements

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563).
Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.
