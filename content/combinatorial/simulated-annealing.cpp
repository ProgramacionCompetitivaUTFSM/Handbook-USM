/*
 Description: Optimizes the function `eval` by exploring the neighbor solutions using simulated annealing.
 - `time_limit`: The maximum time to run the algorithm.
 - `t_i`: Initial temperature.
 - `t_f`: Final temperature.
 The algorithm works for both minimization, to maximize you should change `(old_val - new_val)` to `(new_val - old_val)` and (eval_nxt < best) to (eval_nxt > best)
 `P(old_val, new_val, temp)` computes the probability of accepting a worse solution based on the current temperature.
 Usage:
 - `T` is the data type of the answer.
 - `repr` is the data structure of the representation of the solution, it should contain the functions: init,eval,get_neighbor and rollback.
 Tips:
 - Always write your intermediate solution to a file periodically (e.g., every ~1 million iterations) to ensure partial scores if the process is interrupted.
 - To choose a good $t_i$ and $alpha$, start with a high $t_0$ and a low $alpha$, then adjust based on how the temperature and energy function behave.
 Status: Tested with sudoku.
*/
template<class T, class repr>
struct simulated_annealing {
  T val;
  double get_time(){ return chrono::duration<double>(chrono::high_resolution_clock::now().time_since_epoch()).count(); }
  double P(double old_val, double new_val, double temp) { return exp(((old_val-new_val))/temp); }
  simulated_annealing(double time_limit, double t_i, double t_f, repr & q){
    q.init();
    double st = get_time(); val = q.eval();
    while (1){
      double elapsed = get_time()-st;
      if (elapsed > time_limit) break;
      double ela_frac = elapsed/time_limit;
      double temp = t_i*pow(t_f/t_i,ela_frac);
      q.get_neighbor();
      T new_val = q.eval();
      if (new_val < val || ((double)rand())/RAND_MAX < P(val,new_val,temp)){
        val = new_val;
      } else {
        q.rollback();
      }
    }
  }
};