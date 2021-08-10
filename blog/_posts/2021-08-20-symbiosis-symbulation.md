# Symbiosis in Symbulation
#### August 5, 2021 Tiffany-Ellen Vo
- - - 

[comment]: <> (How do I make it so the text is aligned with the picture?)

><img src="https://scontent-sjc3-1.xx.fbcdn.net/v/t1.6435-9/106543962_3538908449476892_6632988677477612051_n.jpg?_nc_cat=110&ccb=1-4&_nc_sid=09cbfe&_nc_ohc=MVm9XlfPXKYAX8k78kl&_nc_ht=scontent-sjc3-1.xx&oh=aff9f72aa230c94ddce73a0e5ab28c3e&oe=6131225E" alt="drawing" width="200"/> Hello! My name is Tiffany-Ellen Vo, I'm currently a senior at UC Santa Cruz, studying computer engineering. I’m especially interested in logic design, robotics, and computer architecture. In my free time, I love rock climbing, baking, and crocheting. To see some of my other projects, check out my GitHub!

- - - 

## Introduction to Symbiosis 
 Through the guidance of my mentor Anya, this summer I have worked on simulating symbiosis, the interaction between two organisms that are often referred as the host and its symbiont. While symbiosis has been simulated using Symbulation, the purpose of this project is to simulate symbiosis using the Empirical library in order to create and understand various types of symbiosis relationships. For this summer, we focused on being able to add symbionts to a host system which would then increase the count of a point system. The original idea is that if the host reaches a certain amount of points, it would then donate a point to the symbiont and if the symbiont reaches a certain amount of points, then the symbiont would donate a point to the host which would then be multiplied by three.

---

 ## Symbiosis Environment
 In order to create symbiosis, we need to create a host with symbionts and create a world to put them in. Header files for the world, host and symbiont were created in order to do so. These files were originally created by the last WAVES participant that worked with Anya, which were then built upon and edited for this summer. 
 
The constructors for each organism were edited to be up-to-date, which additional functions to add symbionts, which would then increase the count when simulating. 

For creating the world, a similar approach was taken for simulating a world in Symbulation. Since we didn't need all the functions and other attributes as the SymWorld in Symbulation, we inherited certain functions that were necessary for this project. For our world, an empirical world constructor was used to birth the organisms. In the world, two different selection methods were used; elite select and tournament select. Elite select picks a set of the most fit individuals for the next generation while tournament select randomly samples a subset of the population and then chooses the most-fit individual in that sample to progress to the next generation. These functions were originally created in Empirical, but changed slightly to fit this project, which is shown for tournament select below.

```
void AvidaGPTournamentSelect(AvidaGPWorld & world, size_t t_size, size_t tourny_count=1) {
    emp_assert(t_size > 0, "Cannot have a tournament with zero organisms.", t_size, world.GetNumOrgs());
    emp_assert(t_size <= world.GetNumOrgs(), "Tournament too big for world.", t_size, world.GetNumOrgs());
    emp_assert(tourny_count > 0);

    emp::vector<size_t> entries;
    for (size_t T = 0; T < tourny_count; T++) {
      entries.resize(0);
      // Choose organisms for this tournament (with replacement!)
      for (size_t i=0; i < t_size; i++) entries.push_back(
        world.GetRandomOrgID()
      );

      double best_fit = world.CalcFitnessID(entries[0]);
      size_t best_id = entries[0];

      // Search for a higher fit org in the tournament.
      for (size_t i = 1; i < t_size; i++) {
        const double cur_fit = world.CalcFitnessID(entries[i]);
        if (cur_fit > best_fit) {
          best_fit = cur_fit;
          best_id = entries[i];
        }
      }

      // Place the highest fitness into the next generation!
      world.DoBirth(world.GetOrgPtr(best_id), best_id, 1 );
    }
  }
```

 ## Problems Encountered
During this summer, I had a lot of internet and power issues which caused delays with the overall progression of this project. Initially we had tried to override the empirical world birth format, known as DoBirth, however there isn't any way to get the original host organism from 'mem' since it's just the genome and not the whole organism. As a result, the elite select and tournament select functions were recreated to fit our DoBirth method for this project.

 ## Conclusion
 I had a great time working on this project despite the delays due to having a multitude of power and internet issues. I've gained valuable skills, such as working with others, and analyzing files. On top of this, the enrichment seminars were really helpful with gaining new perspectives and skills that I will carry into my career. WAVES is a great intersection between computer science and biology, something that was very interesting and also tough for me due to my lack of knowledge in the biology area. My advice for the next onboarding student is to communicate well with your mentors and team when you feel overwhelmed! Empirical is such a large library and while very interesting, most files will not be necessary for your own project. 


# Acknowledgements 
Thank you so much to the WAVES team for putting this workshop together! It's been a blast to work with you all, and I wish you all the best going forward! From the group meetings to Matthew's ice breakers, it's been a great summer.

Special thanks to my mentor, Anya Vostinar for guiding me throughout this summer and being patient with me. 