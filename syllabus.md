---
layout: default
title: Syllabus
description: Class syllabus
---

## Instructors

* [Matthew Andres Moreno](https://mmore500.github.io)
  * Graduate Student
  * Computer Science and Engineering
  * Ecology, Evolutionary Biology, and Behavior
  * [mmore500@msu.edu](mmore500@msu.edu)
* [Dr. Charles Ofria](https://ofria.com)
  * Professor
  * Computer Science and Engineering
  * [ofria@msu.edu](ofria@msu.edu)
* [Dr. William (Bill) Punch](http://www.cse.msu.edu/~punch/)
  * Associate Professor
  * Computer Science and Engineering
  * [punch@cse.msu.edu](punch@cse.msu.edu)

## Meeting Place and Time

Location TBD

Time TBD

## Office Hours

Available immediately following class or by appointment.

## Course Objectives

* Survey modern C++ features
* Learn C++ best practices
* Develop technical writing proficiency
* Gain familiarity with C++ learning resources online
* Practice facilitating and contributing to a productive and inclusive round table discussion
* Meet other nifty C++ enthusiasts on campus!

## Possible Course Topics

* useful compiler flags
* differences between compilers?
* debuggers/profilers/static Analyzers (e.g., Clang sanitizers)
* fold expressions
* custom allocators
* undefined behavior in C++
* literal strings/C-strings/escape sequences
* command-line arguments
* enumerated classes
* using and typedef
* friends
* constexpr and consteval
* string_view
* how unions work (std::variant)
* lambda powers (capture nuances, mutable lambdas, templated lambdas)
* smart pointers (weak, unique, shared, etc)
* casting (C-style, const_cast, dynamic_cast, reinterpret_cast, static_cast)
* memory management
* ranges library
* move semantics/forwarding
* structured bindings
* concurrency techniques
* thread safety/mutexes
* class-template argument deduction
* object-oriented programming
* serialization/deserialization
* template specialization (and partial specialization)
* template meta-progamming
* substitution failure is not an error (SFINAE)
* curiously recurring template pattern (CRTP)
* random number generators
* std::filesystem
* the dark side of C++: MACROS
* Emscripten - C++ -> Javascript
* what is an application-binary interface (ABI)
* name mangling (and extern)
* move semantics
* concepts
* C++20/23/... features
* the C++ Core Guidelines

## Course Assignments

### Attendance and Participation

* We expect consistent engagement with class discussion and encourage active class participation.
* Students should come to class prepared, having read and/or watched pre-class learning materials.
* Two unexcused absences are allotted.

### Discussion Leader

* Students will be responsible for leading one class session.
* Select pre-class learning materials.
  * Aim for one to two hours of content.
  * (e.g., videos, blog posts, and/or documents or code snippets)
  * Open a pull request [on the course website](https://github.com/mmore500/cse-891) to publish brief descriptions of the selected materials and links to access the materials on the course schedule.
  You'll need to edit the relevant `discussion/_posts/2019-11-20-week??.md` file.
* Prepare at least five conversation-starters/questions.
  * Include these in the pull request that adds to the course schedule.
* Complete preparation at least five days before the class session you are scheduled to lead.
* Facilitate in-class discussion.
* Consult [the course schedule page]({{ site.baseurl }}/schedule.html) for discussion leader assignments.

### Blog Post Author

Students will author two technical posts on the class blog.
Blog posts should describe a use case for a C++ feature or library and/or compare alternate approaches to solving a problem with C++.
Posts should provide original evidence to (code snippets with specific discussion about readability or maintainability, intermediate representation output, execution timings, etc.).
Blog posts (even by the same author) may cover the same topic, but each should present unique original evidence.
Four checkpoint deliverables, listed below, will be assessed for each blog post.
[The course schedule page]({{ site.baseurl }}/schedule.html) lists checkpoint deadlines for both blog posts.

1. topic
  * Open a pull request [on the course website](https://github.com/mmore500/cse-891) that adds a template post with a descriptive title.
  You'll need to create a new file in `blog/_posts/`.
  Use a file that already exists in that directory as a template.
  * Mark your pull request with the "topic" label and comment on the pull request with a brief description of your post.
  * Consider referring to the [Possible Course Topics](#possible-course-topics) subsection
2. outline
    * Curate, as applicable, one or more of the following:
        * illustrative code snippets,
        * embedded components (e.g., [Compiler Explorer](https://godbolt.org/) sandboxes), or
        * graphs and/or tables of execution timings.
    * List references.
        * Any text included verbatim should be designated with `"` or `>` (block quotes) and attributed.
        * Any code included verbatim should be attributed with inline comments or in the post's body.
    * Push to update your pull request and update the label to "outline."
3. rough draft
  * Flesh out full, best-effort prose for your post.
  * Push to update the post's pull request and update the label to "rough draft."
4. completed draft
  * Incorporate reviewer suggestions or briefly justify objection.
  * (In addition to peer reviewers, instructors may also provide suggestions.)
  * Push to update the post's pull request and update the label to "completed draft."

### Blog Post Reviewer

Students will provide two reviews for peers' blog posts.
[The course schedule page]({{ site.baseurl }}/schedule.html) lists reviewer assignments and review deadlines.
Reviews should comprise the following:
* line edits,
  * Suggest specific changes and/or note frequently occurring issues and
  * advise on relevant memes and GIFs (as applicable 😉).
* high-level comments, and
  * Constructively critique organization, subsection lengths, assumed reader background knowledge, author voice and style, etc.
* reader experience feedback.
  * What was it like reading the post?
  * What were your takeaways from the post?

Share reviews as a comment on the post's pull request.

## Final Examination

There will be no final examination for this course.

## Course Schedule

See [the course schedule page]({{ site.baseurl }}/schedule.html) for up-to-date information on deadlines.
[The discussion topics page]({{ site.baseurl }}/schedule.html) lists upcoming .

## Grading

Course points will be divided between assignments as follows.

Category          | Points %
----------------- | --------
Attendance        | 30%
Discussion leader | 20%
Blog post 1       | 20%
Blog post 2       | 20%
Blog post reviews | 10%

All work will receive full credit on successful completion, with points potentially deducted for tardiness.
If instructors deem assignments unsatisfactorily completed, students will be allowed to re-submit work but may be penalized for tardiness.
(See the [Late Work Policy](#late-work-policy).)

Note that *both* blog post reviews are considered as *one* assignment.

Course grades will be determined from course points as follows.

Grade | Overall %
------| ----------
4.0   | >=91
3.5   | >=83
3.0   | >=76
2.5   | >=68
2.0   | >=62
1.5   | >=55
1.0   | >=45

## Late Work Policy

Deadlines are enforced at 11:59pm EST.

### Blog Post Author

Blog post credit (before review) will be calculated based on the following rubric based on days late summed over each checkpoint.

Days Late                      | Credit %
------------------------------ | ----------
0                              | 100%
0 to 1                         | 90%
1 to 2                         | 80%
2 to 3                         | 70%
3 to 7                         | 60%
7+                             | 20%
ready for review after 4/17/20 | 0%
complete after 5/1/20          | 0%

### Blog Post Reviewer

Blog post review credit will be calculated from total days late (over both assignments) based on the following rubric.
(After seven days, instructors will step in to provide review.)

Days Late | Credit %
--------- | --------
0         | 100%
0 to 2    | 80%
2 to 7    | 60%
7+        | 0%

### Discussion Leader

Discussion leader materials preparation credit will be assigned based on the following rubric.
(
After one day late, instructors will step in to prepare materials.
If you end up needing to reschedule your discussion lead day, please email the instructors ASAP.
)

Days Late | Credit %
--------- | --------
0         | 100%
0 to 1    | 80%
1+        | 0%

### No-Penalty Late Days

We afford three no-penalty late days for blog checkpoints and blog review.
(Late days do not apply to discussion materials preparation.)
Email the instructors before turning your assignment in (preferably, before or at the original deadline) to use them.

If a blog post is prepared for review late, the post's reviewer will be provided an automatic commensurate extension with none of *their* no-penalty late days deducted.
If a blog post is not prepared for review by 4/17/20, the blog post's reviewer will not be required to complete a review and will receive full credit for the review assignment.

If a blog post's review is completed late, the post's author will be provided an automatic commensurate extension with none of *their* no-penalty late days deducted.

## Required Materials

A no-cost [GitHub](https://github.com/) account is required to complete course assignments.
If you are not comfortable associating your name with your published class work, you may open an anonymous GitHub account.
If the name listed in the course roster is not included on your GitHub account's profile page, please inform the instructors of your GitHub username by email.

## Electronic Devices Policy

Laptops are encouraged in class!
They're useful for live coding and googling arcane C++ questions.
However, for your own educational benefit and out of consideration of your classmates, please limit your laptop use to class-related activities (e.g., *not* social media, news sites, or homework).

## Spartan Code of Honor Academic Pledge

*Adapted from Dr. Sean Couch's [fall 2018 CMSE 822 syllabus](https://cmse822.github.io/).*

As a Spartan, I will strive to uphold values of the highest ethical standard.
I will practice honesty in my work, foster honesty in my peers, and take pride in knowing that honor is worth more than grades.
I will carry these values beyond my time as a student at Michigan State University, continuing the endeavor to build personal integrity in all that I do.

## Academic Integrity

*Adapted from the MSU Ombudsperson's [Course Syllabus FAQ](https://ombud.msu.edu/classroom-policies/syllabus-faq.html).*

Article 2.3.3 of the [Academic Freedom Report](http://splife.studentlife.msu.edu/academic-freedom-for-students-at-michigan-state-university) states
> The student shares with the faculty the responsibility for maintaining the integrity of scholarship, grades, and professional standards.
In addition, the Department of Computer Science and Engineering adheres to the policies on academic honesty as specified in General Student Regulations 1.0,
Protection of Scholarship and Grades; the all-University Policy on Integrity of Scholarship and Grades; and Ordinance 17.00, Examinations.
(See [Spartan Life: Student Handbook and Resource Guide](http://splife.studentlife.msu.edu/))

Therefore, unless authorized by your instructor, you are expected to complete all course assignments, including homework, projects, quizzes, tests and exams, without assistance from any source.
You are expected to develop original work for this course; therefore, you may not submit course work you completed for another course to satisfy the requirements for this course.
Students who violate MSU academic integrity rules may receive a penalty grade, including a failing grade on the assignment or in the course.
Contact your instructor if you are unsure about the appropriateness of your course work.
(See also the [Academic Integrity webpage](https://msu.edu/~ombud/academic-integrity/index.html).)

## Accommodations for Persons with Disabilities

*Adapted from the MSU Ombudsperson's [Course Syllabus FAQ](https://ombud.msu.edu/classroom-policies/syllabus-faq.html).*

Michigan State University is committed to providing equal opportunity for participation in all programs, services and activities.
Requests for accommodations by persons with disabilities may be made by contacting the Resource Center for Persons with Disabilities at 517-884-RCPD or on the web at [www.rcpd.msu.edu](https://www.rcpd.msu.edu).
Once your eligibility for an accommodation has been determined, you will be issued a verified individual services accommodation (“VISA”) form.
Please present this form to the instructors and lab coordinator at the start of the term or two weeks prior to the first accommodation date.
Requests received after this date may not be honored.

## Code of Conduct

*Adapted from [Contributor Covenant, version 2.0](https://www.contributor-covenant.org/version/2/0/code_of_conduct).*

We as members, contributors, and leaders pledge to make participation in our community a harassment-free experience for everyone, regardless of age, body size, visible or invisible disability, ethnicity, sex characteristics, gender identity and expression, level of experience, education, socio-economic status, nationality, personal appearance, race, religion, or sexual identity and orientation.

We pledge to act and interact in ways that contribute to an open, welcoming, diverse, inclusive, and healthy community.

Examples of behavior that contributes to a positive environment for our community include:

* Demonstrating empathy and kindness toward other people
* Being respectful of differing opinions, viewpoints, and experiences
* Giving and gracefully accepting constructive feedback
* Accepting responsibility and apologizing to those affected by our mistakes, and learning from the experience
* Focusing on what is best not just for us as individuals, but for the overall community

Examples of unacceptable behavior include:

* The use of sexualized language or imagery, and sexual attention or
  advances of any kind
* Trolling, insulting or derogatory comments, and personal or political attacks
* Public or private harassment
* Publishing others' private information, such as a physical or email
  address, without their explicit permission
* Other conduct which could reasonably be considered inappropriate in a
  professional setting

Instances of abusive, harassing, or otherwise unacceptable behavior may be reported to course instructors.
All complaints will be reviewed and investigated promptly and fairly.

All community leaders are obligated to respect the privacy and security of the reporter of any incident.

## Disruptive Behavior

*Adapted from the MSU Ombudsperson's [Course Syllabus FAQ](https://ombud.msu.edu/classroom-policies/syllabus-faq.html).*

Article 2.III.B.4 of the [Student Rights and Responsibilities (SRR)](http://splife.studentlife.msu.edu/academic-freedom-for-students-at-michigan-state-university) for students at Michigan State University states: "The student's behavior in the classroom shall be conducive to the teaching and learning process for all concerned."
Article 2.III.B.10 of the [SRR](http://splife.studentlife.msu.edu/academic-freedom-for-students-at-michigan-state-university) states that "The student and the faculty share the responsibility for maintaining professional relationships based on mutual trust and civility."
[General Student Regulation 5.02](http://splife.studentlife.msu.edu/regulations/general-student-regulations) states: "No student shall . . . interfere with the functions and services of the University (for example, but not limited to, classes . . .) such that the function or service is obstructed or disrupted.
Students whose conduct adversely affects the learning environment in this classroom may be subject to disciplinary action.

## Grief Absence Policy

*Adapted from Dr. Katy Colbry's spring 2020 EGR 393 syllabus.*

Michigan State University is committed to ensuring that the bereavement process of a student who loses a family member during a semester does not put the student at an academic disadvantage in their classes.
If you require a grief absence, you should complete the [“Grief Absence Request” web form](https://reg.msu.edu/StuForms/Stuinfo/GriefAbsenceForm.aspx) no later than one week after knowledge of the circumstance.
I will work with you to make appropriate accommodations so that you are not penalized due to a verified grief absence.

## Attendance

*Adapted from the MSU Ombudsperson's [Course Syllabus FAQ](https://ombud.msu.edu/classroom-policies/syllabus-faq.html).*

Students who fail to attend the first four class sessions or class by the fifth day of the semester, whichever occurs first, may be dropped from the course.

## Limits to Confidentiality

*Adapted from the MSU Ombudsperson's [Course Syllabus FAQ](https://ombud.msu.edu/classroom-policies/syllabus-faq.html).*

Essays, journals, and other materials submitted for this class are generally considered confidential pursuant to the University's student record policies.
However, students should be aware that University employees, including instructors, may not be able to maintain confidentiality when it conflicts with their responsibility to report certain issues to protect the health and safety of MSU community members and others.
As the instructor, I must report the following information to other University offices (including the [MSU Police Department](http://police.msu.edu/)) if you share it with me:

* Suspected child abuse/neglect, even if this maltreatment happened when you were a child,
* Allegations of sexual assault or sexual harassment when they involve MSU students, faculty, or staff, and
* Credible threats of harm to oneself or to others.

These reports may trigger contact from a campus official who will want to talk with you about the incident that you have shared.
In almost all cases, it will be your decision whether you wish to speak with that individual.
If you would like to talk about these events in a more confidential setting you are encouraged to make an appointment with the [MSU Counseling Center](http://counseling.msu.edu/).

## Campus Emergencies

*Adapted from the MSU Ombudsperson's [Course Syllabus FAQ](https://ombud.msu.edu/classroom-policies/syllabus-faq.html).*

If an emergency arises in this classroom, building or vicinity, your instructor will inform you of actions to follow to enhance your safety.
As a student in this class, you are responsible for knowing the location of the nearest emergency evacuation route or shelter.
These directions appear on the maps posted on the walls throughout this building.
If police or university officials order us to evacuate the classroom or building, follow the posted emergency route in an orderly manner and assist those who might need help in reaching a barrier-free exit or shelter.
To receive emergency messages, set your cellular phones on silent mode when you enter this classroom.
If you observe or receive an emergency alert, immediately and calmly inform your instructor.
(See also www.alert.msu.edu.)

(Adopted from "Handling Emergency Situations," by F/Lt Penny Fisher, MSU Department of Public Safety.)
