/*
 *Description:* Halfplane intersection
 *Status:* Partially tested
*/
const ld inf = 1e18;
const ld eps = 1e-9;
vector<point2d<ld>> hp_intersect(vector<halfplane> &H) {
  point2d<ld> box[4] = {{inf, inf}, {-inf, inf}, {-inf, -inf}, {inf, -inf}};
  for (int i = 0; i < 4; i++) {
    halfplane aux(box[i], box[(i + 1) % 4]);
    H.push_back(aux);
  }
  sort(H.begin(), H.end());
  deque<halfplane> dq;
  int len = 0;
  for (int i = 0; i < H.size(); i++) {
    while (len > 1 && H[i].out(inter(dq[len - 1], dq[len - 2])))
      dq.pop_back(), --len;
    while (len > 1 && H[i].out(inter(dq[0], dq[1])))
      dq.pop_front(), --len;
    if (len > 0 && fabsl((H[i].pq ^ dq[len - 1].pq)) < eps) {
      if ((H[i].pq | dq[len - 1].pq) < 0.0)
        return vector<point2d<ld>>();
      if (H[i].out(dq[len - 1].p))
        dq.pop_back(), --len;
      else
        continue;
    }
    dq.push_back(H[i]), ++len;
  }
  while (len > 2 && dq[0].out(inter(dq[len - 1], dq[len - 2])))
    dq.pop_back(), --len;
  while (len > 2 && dq[len - 1].out(inter(dq[0], dq[1])))
    dq.pop_front(), --len;
  if (len < 3)
    return vector<point2d<ld>>();
  vector<point2d<ld>> ret(len);
  for (int i = 0; i + 1 < len; i++)
    ret[i] = inter(dq[i], dq[i + 1]);
  ret.back() = inter(dq[len - 1], dq[0]);
  return ret;
}
