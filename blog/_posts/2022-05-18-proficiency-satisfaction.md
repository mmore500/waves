---
layout: post
title: "WAVES Workshop Learning Outcomes"
date: 2022-05-18
author: Matthew Andres Moreno
---

Mirroring the modernization of medicine and agriculture, critical, evidence-driven assessment has proven a key unifying element to guide improvement to educational practice [(Davies, 1999)](#davies1999what).
In particular, the difficulty and subtlety of persistent social inequalities within STEM education suggests a crucial role for empirical study in their remedy ([Ballen et al., 2017](#ballen2017enhancing); [Theobald et al., 2020](#theobald2020active)).

Evidence-driven assessment can fulfill an additional role, too, in demonstrating the efficacy of existing educational practice to stakeholders [(Groccia and Buskist, 2011)](#groccia2011need).

In these veins, we used entry and exit surveys assess participant outcoes from the 2020 and 2021 Workshop for Avida-ED Software Development (WAVES) program.
We find significant improvements in participants' self-reported proficiencies with C++, JavaScript, and HTML/CSS over the course of the workshop, with members of underadvantaged groups in computer science generally starting at a lower self-reported proficiency but gaining more proficiency during the workshop than their peers.
Interestingly, we also observed a higher proportion of underadvantaged students report themselves as "very satisfied" with the workshop compared to their peers.
However, among all participants, we did not observe improvements in participants' self-reported overall programming proficiency nor their proficiency in evolutionary thinking.

## Workshop Recap

The WAVES program was a series of two ten-week fully-remote, fully-funded focused on early-career research and software development offered in 2020 and 2021.
Workshop curriculum centered around on independent work on a mentored software engineering or other research project.
However, the workshop also included an intensive first-week tutorial series on technologies for deploying scientific software into the web browser (Emscripten and Empirical), weekly professional development enrichment seminars, and weekly all-hands check-in meetings.

The goal of the workshop was four-fold:

1. to help participants advance their careers by skillbuilding through hands-on C++ and/or JavaScript software development in an academic setting,
2. to catalyze effective science communication and science pedagogy by helping participants develop the know-how to showcase their research through interactive web applications,
3. to jumpstart software development on web framework and core digital evolution tools in support of the next version of the Avida-ED scientific and educational software, and
4. to produce software that broadly enriches the digital evolution, scientific, education, and open-source communities.

Objectives 3 and 4 are directly geared towards participants' project artifacts themselves (i.e., software, documentation, blog posts, etc.).
However, by their very nature, assessing the workshop's success in reaching objectives 1 and 2 requires measuring participants' learning.
In order to facilitate summative assessment of participant learning outcomes [(Dixson and Worrell, 2016)](#dixson2016formative), we performed a pre- and post-workshop electronic surveys of all participants.

## Workshop Demographics

The workshop hosted 27 total participants (17 in 2020 and 10 in 2021).
In 2020, 15 participants were undergraduates, 1 participant was a graduate student, and 1 workshop participant was a postdoc.
In 2021, 9 participants were undergraduates and 1 participant was a graduate student.

In 2020, ten participants identified as women (59%).
Seven participants identified as men (41%).
Three participants (18%) identified as of Hispanic, Latino, or Spanish Origin.
Three participants identified as Black or African-American (18%), one identified as Asian Indian (6%), two identified as Chinese (12%), and twelve identified as White (71%).
One participant identified as a first-generation college student (6%).

Five participants identified as women (50%).
Five participants identified as men (50%).
One participant identified as Korean (10%), one identified as Vietnamese (10%), two identified as Other Asian (20%), and eight identified as White (80%).
Three participants identified as LGBTQIAP (30%).
One participant identified as first-generation (10%).

In line with the NSF, we considered participants who self-identified as women, African Americans, Hispanics, American Indians, Alaska Natives, Native Hawaiians, and Pacific Islanders as members of an underadvantaged group in computer science.
Although it was not directly queried in our surveys, we considered participants who reported LGBTQIAP+ identity as "Other Identity" as members of an underadvantaged group, as well ([Dym et al., 2021](#dym2021you); [Stout and Wright, 2016](#stout2016lesbian)).
Disability was also not directly queried in our surveys, and we didn't have any participants report a disability identity as "Other Identity."

We counted 21 of 27 (77%) workshop participants as members of an underadvantaged group (14/17 or 82% in 2020 and 7/10 or 70% in 2021).
Because of anonymity concerns due to the small sample size, we do not disaggregate analyses beyond participants' membership in an underadvantaged group [(Bhatti, 2021)](#bhatti2021toward).

## C++, JavaScript, and HTML/CSS Proficiencies

In pre- and post-workshop surveys, we asked participants to rate their proficiency with C++, JavaScript, and HTML/CSS using the following scale (with $x$ substituted for C++, JavaScript, then HTML/CSS).

> How comfortable are you with $x$?
>
> 1. I have not used the language
> 2. I have minimally used this language and/or I have not yet applied it to a project
> 3. I have some experience with this language and am ready to tackle larger projects in it
> 4. I have completed substantial, independent projects using this language

![C++ proficiency outcomes]({{ site.baseurl }}/assets/mmore500/cpp-proficiency-all.PNG){:style="width: 100%;"}
[**Figure SRPCP.**](#fig-srpcp){:id="fig-srpcp"}
*Self-reported participant C++ proficiency measured on workshop entry and exit survey.
Error bar denotes bootstrapped 95% confidence interval.*

[Figure SRPCP](#fig-srpcp) summarizes self-reported C++ proficiency before and after the workshop.
More than half of participants rated themselves as more proficient at C++ after the workshop ended compared to when it began.
Self-reported C++ proficiency increased significantly a mean of around 0.75 proficiency levels (strictly positive 95% confidence interval).

![JavaScript proficiency outcomes]({{ site.baseurl }}/assets/mmore500/javascript-proficiency-all.PNG){:style="width: 100%;"}
[**Figure SRPJP.**](#fig-srpjp){:id="fig-srpjp"}
*Self-reported participant JavaScript proficiency measured on workshop entry and exit survey.
Error bar denotes bootstrapped 95% confidence interval.*

[Figure SRPJP](#fig-srpjp) summarizes self-reported JavaScript proficiency before and after the workshop.
About half of participants rated themselves as more proficient at JavaScript after the workshop ended compared to when it began.
Two reported themselves less proficient.
Self-reported JavaScript proficiency increased significantly a mean of around 0.45 proficiency levels (strictly positive 95% confidence interval).

![HTML/CSS proficiency outcomes]({{ site.baseurl }}/assets/mmore500/dom-proficiency-all.PNG){:style="width: 100%;"}
[**Figure SRPHP.**](#fig-srphp){:id="fig-srphp"}
*Self-reported participant HTML/CSS proficiency measured on workshop entry and exit survey.
Error bar denotes bootstrapped 95% confidence interval.*

[Figure SRPHP](#fig-srphp) summarizes self-reported HTML/CSS proficiency before and after the workshop.
About half of participants rated themselves as more proficient at JavaScript after the workshop ended compared to when it began.
One reported themself less proficient.
Self-reported JavaScript proficiency increased significantly a mean of around 0.25 proficiency levels (strictly positive 95% confidence interval).

## C++, JavaScript, and HTML/CSS Proficiencies in Members of Underadvantaged Groups

![Disaggregated C++ proficiency outcomes]({{ site.baseurl }}/assets/mmore500/cpp-proficiency-disaggregated.PNG){:style="width: 100%;"}
[**Figure DSRPC.**](#fig-dsrpc){:id="fig-dsrpc"}
*Disaggregated self-reported participant C++ proficiency measured on workshop entry and exit survey.
Error bar denotes bootstrapped 95% confidence interval.*

![Disaggregated JavaScript proficiency outcomes]({{ site.baseurl }}/assets/mmore500/javascript-proficiency-disaggregated.PNG){:style="width: 100%;"}
[**Figure DSRPJ.**](#fig-dsrpj){:id="fig-dsrpj"}
*Disaggregated self-reported participant JavaScript proficiency measured on workshop entry and exit survey.
Error bar denotes bootstrapped 95% confidence interval.*

![Disaggregated HTML/CSS proficiency outcomes]({{ site.baseurl }}/assets/mmore500/dom-proficiency-disaggregated.PNG){:style="width: 100%;"}
[**Figure DSRPH.**](#fig-dsrph){:id="fig-dsrph"}
*Disaggregated self-reported participant HTML/CSS proficiency measured on workshop entry and exit survey.
Error bar denotes bootstrapped 95% confidence interval.*

Figures [DSRPC](#fig-dsrpc), [DSRPJ](#fig-dsrpj), and [DSRPH](#fig-dsrph) disaggregate members of underadvantaged groups' self-reported proficiencies on C++, JavaScript, and HTML/CSS.
For all three languages, these members entered and exited the workshop with on-average lower self-rated proficiency.
However, for C++ and JavaScript members of underadvantaged groups gained on average more self-reported proficiency units, potentially representing success of the workshop in "catching up" these participants.

Although some comparisons might appear significant due to non-overlapping 95% confidence intervals, sample size is too small to reliably interpret the bootstrapped bars.
The effect of some participants entering with no room for detectable improvement (i.e., rating themselves the highest available proficiency) must also be considered when interpreting results.

## Programming Proficiency

In addition to asking about specific programming languages, we also asked participants to report their overall programming skill.

> Which describes your overall level of proficiency with programming?
>
> 0. I have no experience with programming
> 1. I have some exposure to programming (e.g., coursework that used some programming or online programming tutorials)
> 2. I have completed an introductory-level programming sequence (e.g., at least 1 year of programming courses)
> 3. I have programmed large projects (e.g., a capstone to a CS degree, substantial on the job training, or large personal projects)
> 4. I have done extensive programming work (e.g., a full time job for multiple years, or many years of personal projects)

![Programming proficiency outcomes]({{ site.baseurl }}/assets/mmore500/programming-proficiency-all.PNG){:style="width: 100%;"}
[**Figure SRPPM.**](#fig-srppm){:id="fig-srppm"}
*Self-reported programming proficiency measured on workshop entry and exit surveys.
Error bar denotes bootstrapped 95% confidence interval.*

![Disaggregated programming proficiency outcomes]({{ site.baseurl }}/assets/mmore500/programming-proficiency-disaggregated.PNG){:style="width: 100%;"}
[**Figure DSRPP.**](#fig-srpsm){:id="fig-srpsm"}
*Disaggregated self-reported programming proficiency measured on workshop entry and exit surveys.
Error bars denotes bootstrapped 95% confidence interval.*

As shown in [Figure SRPPM](#fig-srppm), we did not observe increases in self-rated overall proficiency in programming associated with WAVES.
In fact, mean self-rated proficiency decreased over the course of the workshop.
[Figure DSRPP](#fig-dsrpp) shows that status as a member of an underadvantaged group did not notably affect overall programming proficiency outcome.
This result suggests that enrichment content on more general programming topics might benefit the workshop experience.
However, this result might potentially be due to too-coarse and overly-career-oriented design of the response options.

## Evolution Proficiency

Because of the evolution education mission of Avida-ED, we had participants reported their proficiency with evolutionary thinking according to the following scale.

> How comfortable are you with evolutionary biology?
>
> 1. I am unfamiliar with the fundamental mechanisms of evolution
> 2. I am familiar with the fundamental mechanisms of evolution
> 3. I am interested in open questions about evolution
> 4. I feel comfortable engaging with talks and papers about contemporary evolution research
> 5. I feel comfortable creating hypotheses based on evolutionary thinking

![Evolution proficiency outcomes]({{ site.baseurl }}/assets/mmore500/evolution-proficiency-all.PNG){:style="width: 100%;"}
[**Figure SRETP.**](#fig-sretp){:id="fig-sretp"}
*Self-reported evolutionary thinking proficiency measured on workshop entry and exit surveys.
Error bar denotes bootstrapped 95% confidence interval.*

[Figure SRETP](#fig-sretp) shows nearly no change in participant evolutionary thinking over the course of the workshop.
As before, this result suggests that improved enrichment content on evolution topics might benefit the workshop experience.
However, this result might potentially be due to too-coarse response options as well.

![Evolution proficiency outcomes]({{ site.baseurl }}/assets/mmore500/evolution-proficiency-disaggregated.PNG){:style="width: 100%;"}
[**Figure DSRET.**](#fig-dsret){:id="fig-dsret"}
*Disaggregated self-reported evolutionary thinking proficiency measured on workshop entry and exit surveys.
Error bars denote bootstrapped 95% confidence interval.*

Disaggregating by underadvantaged status in [Figure DSRET](#fig-dsret), we can see that underadvantaged students entered and exited with marginally higher mean proficiency with evolutionary thinking.
However, non-underadvantaged students gained somewhat more proficiency over the course of the workshop.

## Workshop Satisfaction

Finally, we asked 2021 participants to rate their overall satisfaction with the workshop according to the following scale.

> How would you rate your experience with the workshop?
> * Very satisfied
> * Satisfied
> * Neutral
> * Dissatisfied
> * Very dissatisfied

This question was not administered to 2020 participants.

![Workshop satisfaction outcomes]({{ site.baseurl }}/assets/mmore500/participant-satisfaction.PNG){:style="width: 100%;"}
[**Figure SRPSM.**](#fig-srpsm){:id="fig-srpsm"}
*Self-reported participant satisfaction measured on workshop exit survey.
Note that workshop satisfaction data was only collected in 2021.*

[Figure SRPSM](#fig-srpsm) summarizes participant satisfaction with the workshop.
All participants were "satisfied" or "very satisfied."
Six were "very satisfied" and four were "satisfied."

Interestingly, disaggregating shows a higher fraction of members of an underadvantaged group rating themselves "very satisfied."
However, due to small sample size this result is not statistically significant (Fisher's Exact Test).

## Conclusion

Survey data suggests the WAVES workshop succeeded in building language-specific proficiency among participants, particularly with respect to "catching up" members of underadvantaged groups.
However, survey data shows that the the workshop did not improve participant evolutionary thinking or overall self-assessed programming proficiency.
This suggests areas for potential curriculum improvement if the workshop were to be offered again.

In future work with existing survey data, we are interested in studying the impact of adding social "warm-up" activities to enrichment seminars in 2021, particularly with respect to participants' sense of community within the virtual workshop context.
The potential relationship between strengthened professional social relationships and retention of members of underadvantaged groups makes this question particularly prescient [(Merolla and Serpe, 2013)](#merolla2013stem).

We are also interested in comparing applicant demographic data collected in 2021 to the demographics of selected workshop participants in order to reflect on the workshop admissions process.

## Data & Software

Survey data is stored on the [Open Science Framework](https://osf.io).
The data repository page can be accessed at <https://osf.io/asf3b/> (DOI `10.17605/OSF.IO/ASF3B`).
Raw survey response data and collated, coded (i.e., assigned numerical labels to survey responses), and partially anonymized data is contained within a protected sub-component of that project, located at `https://osf.io/urv7w/`.

We have pre- and post-workshop survey responses for all participants, except for one student from 2020 who we were not able to reach after the workshop concluded.
Based on the pre-workshop survey data, this participant identified as a member of an underadvantaged group in computer science.
This participant's post-workshop survey data was excluded from all analyses because it was missing.

To minimize stereotype threat effects, participants self-reported demographic information as the final component of each survey [(Steele and Aronson, 1995)](#steele1995stereotype).

Data analyses are organized as a notebook, [available on GitHub](https://github.com/mmore500/waves/blob/master/assets/WAVES_proficiency_and_satisfaction.ipynb)

## Acknowledgment

This work is supported through Active LENS: Learning Evolution and the Nature of Science using Evolution in Action (NSF IUSE #1432563).
Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

This research was supported in part by NSF grants DEB-1655715 and DBI-0939454.
This material is based upon work supported by the National Science Foundation Graduate Research Fellowship under Grant No. DGE-1424871.
Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.


## References

<a
  href="https://doi.org/10.1187/cbe.16-12-0344"
  id="ballen2017enhancing">
Ballen, Cissy J., et al. "Enhancing diversity in undergraduate science: Self-efficacy drives performance gains with active learning." CBE—Life Sciences Education 16.4 (2017): ar56.
</a>

<a
  href="https://doi.org/10.1128/jmbe.00202-21"
  id="bhatti2021toward">
Bhatti, Haider Ali. "Toward “inclusifying” the underrepresented minority in STEM education research." Journal of Microbiology & Biology Education 22.3 (2021): e00202-21.
</a>

<a
  href="https://doi.org/10.1145/3287324.3287332"
  id="camp2019new">
Camp, Tracy, et al. "The new NSF requirement for broadening participation in computing (BPC) plans: Community advice and resources." Proceedings of the 50th ACM Technical Symposium on Computer Science Education. 2019.
</a>

<a
  href="https://doi.org/10.1111/1467-8527.00106"
  id="davies1999what">
Davies, Philip. "What is evidence‐based education?." British journal of educational studies 47.2 (1999): 108-121.
</a>

<a
  href="https://doi.org/10.1080/00405841.2016.1148989"
  id="dixson2016formative">
Dixson, Dante D., and Frank C. Worrell. "Formative and summative assessment in the classroom." Theory into practice 55.2 (2016): 153-159.
</a>

<a
  href="https://doi.org/10.5195/jmla.2017.88"
  id="foster2017open">
Foster, Erin D., and Ariel Deardorff. "Open science framework (OSF)." Journal of the Medical Library Association: JMLA 105.2 (2017): 203.
</a>

<a
  href="https://doi.org/10.1002/tl.463"
  id="groccia2011need">
Groccia, James E., and William Buskist. "Need for evidence‐based teaching." New directions for teaching and learning 2011.128 (2011): 5-11.
</a>

<a
  href="https://doi.org/10.1007/s11218-013-9233-7"
  id="merolla2013stem">
Merolla, David M., and Richard T. Serpe. "STEM enrichment programs and graduate school matriculation: the role of science identity salience." Social Psychology of Education 16.4 (2013): 575-597.
</a>

<a
  href="https://psycnet.apa.org/doi/10.1037/0022-3514.69.5.797"
  id="steele1995stereotype">
Steele, Claude M., and Joshua Aronson. "Stereotype threat and the intellectual test performance of African Americans." Journal of personality and social psychology 69.5 (1995): 797.
</a>

<a
  href="https://doi.org/10.1109/MCSE.2016.45"
  id="stout2016lesbian">
Stout, Jane G., and Heather M. Wright. "Lesbian, gay, bisexual, transgender, and queer students' sense of belonging in computing: An Intersectional approach." Computing in Science & Engineering 18.3 (2016): 24-30.
</a>

<a
  href="https://doi.org/10.1073/pnas.1916903117"
  id="theobald2020active">
Theobald, Elli J., et al. "Active learning narrows achievement gaps for underrepresented students in undergraduate science, technology, engineering, and math." Proceedings of the National Academy of Sciences 117.12 (2020): 6476-6483.
</a>
