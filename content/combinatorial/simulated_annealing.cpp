/*
 * Description: Optimizes the function `eval` by exploring the neighbor solutions using simulated annealing.
 * - `time_limit`: The maximum time to run the algorithm.
 * - `t_0`: Initial temperature.
 * - `t_f`: Final temperature.
 * - `a`: Cooling rate.
 * The algorithm works for both minimization, to maximize you should change `(old_val - new_val)` to `(new_val - old_val)` and (eval_nxt < best) to (eval_nxt > best)
 * `P(old_val, new_val, temp)` computes the probability of accepting a worse solution based on the current temperature.
 * Usage:
 * - `ans` is the data type of the answer.
 * - `repr` is the data structure of the representation of the solution.
 * - `neighbor`: given `repr`, you can get a random neighbor solution.
 * - `eval`: allows to get the evaluation of the representation.
 *
 * Tips:
 * - Always write your intermediate solution to a file periodically (e.g., every ~1 million iterations) to ensure partial scores if the process is interrupted.
 * - To choose a good $t_0$ and $alpha$, start with a high $t_0$ and a low $\alpha$, then adjust based on how the temperature and energy function behave. Use binary search on $\alpha$ to find an optimal cooling rate.
 * - Running the simulated annealing for a longer time with a larger $alpha$ is generally better than restarting with a previous solution and a lower $t_0$.
 * 
 * Status: Tested in DIY Tree (Codeforces).
 */
template<typename ans, class repr, repr neighbor(repr &u), ans eval(repr&)> 
struct simulated_annealing {
  ans best, eval_s;
  simulated_annealing(ld time_limit, ld t_0, ld t_f, ld a) {
    time_t start = clock();
    for(;;) {
      repr s; // Random valid state
      best = eval_s = eval(s);
      for (ld t=t_0; t>=t_f; t*=a) {
        repr next = neighbor(s);
        ans eval_nxt = eval(next);
        if ( (eval_nxt < best)) {
          best = eval_nxt;
          s = next;
        }else if (P(eval_s, eval_nxt, t) > ((ld)rand())/RAND_MAX) {
          s = next;
          eval_s = eval_nxt;
        }
      }
      if((ld)(clock()-start)*1.0/CLOCKS_PER_SEC > time_limit) break;
    }
  }
  ld P(ld old_val, ld new_val, ld temp) {
    return exp((old_val - new_val) / temp);
  }
};
