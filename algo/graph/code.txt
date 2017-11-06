
        This file contains the code from "Algorithms in C++, Third Edition,
        Part 5," by Robert Sedgewick, and is covered under the copyright
        and warranty notices in that book. Permission is granted for this
        code to be used for educational purposes in association with the text,
        and for other uses not covered by copyright laws, provided that
        the following notice is included with the code:

                "This code is from "Algorithms in C++, Third Edition,"
                by Robert Sedgewick, Addison-Wesley, 2002."

        Commercial uses of this code require the explicit written
        permission of the publisher. Send your request for permission,
        stating clearly what code you would like to use, and in what
        specific way, to: aw.cse@aw.com


----------
CHAPTER 17. Graph Properties and Types
-----
struct Edge 
  { int v, w;
    Edge(int v = -1, int w = -1) : v(v), w(w) { }
  };
class GRAPH
  { private:
      // Implementation-dependent code
    public:
      GRAPH(int, bool);
      ~GRAPH();
      int V() const;
      int E() const;
      bool directed() const;
      int insert(Edge);
      int remove(Edge);
      bool edge(int, int);
      class adjIterator
        { 
          public:
            adjIterator(const GRAPH &, int);
            int beg();
            int nxt();
            bool end();
        };
  };
-----
template <class Graph> 
vector <Edge> edges(Graph &G)
  { int E = 0;
    vector <Edge> a(G.E()); 
    for (int v = 0; v < G.V(); v++) 
      {
        typename Graph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()) 
          if (G.directed() || v < w)
            a[E++] = Edge(v, w);
      }
    return a;
  }
-----
template <class Graph> 
void IO<Graph>::show(const Graph &G)
  { 
    for (int s = 0; s < G.V(); s++) 
      {
        cout.width(2); cout << s << ":";
        typename Graph::adjIterator A(G, s);
        for (int t = A.beg(); !A.end(); t = A.nxt()) 
          { cout.width(2); cout << t << " "; }
        cout << endl;
      }
  }
-----
template <class Graph> 
class IO
  {
    public:
      static void show(const Graph &);
      static void scanEZ(Graph &);
      static void scan(Graph &);
  };
-----
template <class Graph> 
class CC
  { 
    private:
      // implementation-dependent code
    public:
      CC(const Graph &);
      int count();
      bool connect(int, int);
  };
-----
#include <iostream.h>
#include <stdlib.h>
#include "GRAPH.cc"
#include "IO.cc"
#include "CC.cc"
main(int argc, char *argv[])
{ int V = atoi(argv[1]);
  GRAPH G(V);
  IO<GRAPH>::scan(G);
  if (V < 20) IO<GRAPH>::show(G);
  cout << G.E() << " edges ";
  CC<GRAPH> Gcc(G);
  cout << Gcc.count() << " components" << endl;
}
-----
class DenseGRAPH
{ int Vcnt, Ecnt; bool digraph;
  vector <vector <bool> > adj;
public:
  DenseGRAPH(int V, bool digraph = false) :
    adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
    { 
      for (int i = 0; i < V; i++) 
        adj[i].assign(V, false);
    }
  int V() const { return Vcnt; }
  int E() const { return Ecnt; }
  bool directed() const { return digraph; }
  void insert(Edge e)
    { int v = e.v, w = e.w;
      if (adj[v][w] == false) Ecnt++;
      adj[v][w] = true;
      if (!digraph) adj[w][v] = true; 
    } 
  void remove(Edge e)
    { int v = e.v, w = e.w;
      if (adj[v][w] == true) Ecnt--;
      adj[v][w] = false;
      if (!digraph) adj[w][v] = false; 
    } 
  bool edge(int v, int w) const 
    { return adj[v][w]; }
  class adjIterator;
  friend class adjIterator;
};
-----
class DenseGRAPH::adjIterator
{ const DenseGRAPH &G;
  int i, v;
public:
  adjIterator(const DenseGRAPH &G, int v) : 
    G(G), v(v), i(-1) { }
  int beg()
    { i = -1; return nxt(); }
  int nxt()
    {
      for (i++; i < G.V(); i++)
        if (G.adj[v][i] == true) return i;
      return -1;
    }
  bool end()
    { return i >= G.V(); }
};
-----
class SparseMultiGRAPH
{ int Vcnt, Ecnt; bool digraph;
  struct node
    { int v; node* next;
      node(int x, node* t) { v = x; next = t; }
    };
  typedef node* link;
  vector <link> adj;
public:
  SparseMultiGRAPH(int V, bool digraph = false) :
    adj(V), Vcnt(V), Ecnt(0), digraph(digraph) 
    { adj.assign(V, 0); }
  int V() const { return Vcnt; }
  int E() const { return Ecnt; }
  bool directed() const { return digraph; }
  void insert(Edge e)
    { int v = e.v, w = e.w;
      adj[v] = new node(w, adj[v]);
      if (!digraph) adj[w] = new node(v, adj[w]); 
      Ecnt++;
    } 
  void remove(Edge e);
  bool edge(int v, int w) const; 
  class adjIterator;
  friend class adjIterator;
};
-----
class SparseMultiGRAPH::adjIterator
{ const SparseMultiGRAPH &G;
  int v;
  link t;
public:
  adjIterator(const SparseMultiGRAPH &G, int v) : 
    G(G), v(v) { t = 0; }
  int beg()
    { t = G.adj[v]; return t ? t->v : -1; }
  int nxt()
    { if (t) t = t->next; return t ? t->v : -1; }
  bool end()
    { return t == 0; }
};
-----
template <class Graph> class DEGREE
{ const Graph &G;
  vector <int> degree; 
public:
  DEGREE(const Graph &G) : G(G), degree(G.V(), 0) 
    { 
      for (int v = 0; v < G.V(); v++)
      { typename Graph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()) 
          degree[v]++;
      }
    }
  int operator[](int v) const 
    { return degree[v]; }
};
-----
static void randE(Graph &G, int E)
  { 
    for (int i = 0; i < E; i++)
      {
        int v = int(G.V()*rand()/(1.0+RAND_MAX));
        int w = int(G.V()*rand()/(1.0+RAND_MAX));
        G.insert(Edge(v,w));
      }
  }
-----
static void randG(Graph &G, int E)
  { double p = 2.0*E/G.V()/(G.V()-1);
    for (int i = 0; i < G.V(); i++)
      for (int j = 0; j < i; j++)
        if (rand() < p*RAND_MAX)
          G.insert(Edge(i, j));
  }
-----
#include "ST.cc"
template <class Graph> 
void IO<Graph>::scan(Graph &G)
  { string v, w;
    ST st;
    while (cin >> v >> w)
      G.insert(Edge(st.index(v), st.index(w)));
  }
-----
#include <string>
class ST 
{ int N, val;
  struct node 
    { int v, d; node* l, *m, *r;
      node(int d) : v(-1), d(d), l(0), m(0), r(0) {}
    };
  typedef node* link;
  link head;
  link indexR(link h, const string &s, int w)
    { int i = s[w];
      if (h == 0) h = new node(i);
      if (i == 0) 
        {
          if (h->v == -1) h->v = N++;
          val = h->v;
          return h;
        }
      if (i < h->d) h->l = indexR(h->l, s, w);
      if (i == h->d) h->m = indexR(h->m, s, w+1);
      if (i > h->d) h->r = indexR(h->r, s, w);
      return h;
    }
public:
  ST() : head(0), N(0) { }
  int index(const string &key)
    { head = indexR(head, key, 0); return val; }
};
-----
template <class Graph> class sPATH
{ const Graph &G;
  vector <bool> visited;
  bool found; 
  bool searchR(int v, int w)
    { 
      if (v == w) return true;
      visited[v] = true;
      typename Graph::adjIterator A(G, v);
      for (int t = A.beg(); !A.end(); t = A.nxt()) 
        if (!visited[t])
          if (searchR(t, w)) return true;
      return false;
    }
public:
  sPATH(const Graph &G, int v, int w) : 
    G(G), visited(G.V(), false) 
    { found = searchR(v, w); }
  bool exists() const 
    { return found; }
};
-----
  bool searchR(int v, int w, int d)
    { 
      if (v == w) return (d == 0);
      visited[v] = true;
      typename Graph::adjIterator A(G, v);
      for (int t = A.beg(); !A.end(); t = A.nxt()) 
        if (!visited[t])
          if (searchR(t, w, d-1)) return true;
      visited[v] = false;
      return false;
    }
-----
template <class Graph> class ePATH
{ Graph G;
  int v, w;
  bool found;
  STACK <int> S;
  int tour(int v);
public:
  ePATH(const Graph &G, int v, int w) : 
    G(G), v(v), w(w)
    { DEGREE<Graph> deg(G);
      int t = deg[v] + deg[w];
      if ((t % 2) != 0) { found = false; return; }
      for (t = 0; t < G.V(); t++)
        if ((t != v) && (t != w))
          if ((deg[t] % 2) != 0) 
            { found = false; return; }
      found = true;
    }
  bool exists() const 
    { return found; }
  void show();
};
-----
template <class Graph>
int ePATH<Graph>::tour(int v)
  { 
    while (true) 
      { typename Graph::adjIterator A(G, v);
        int w = A.beg(); if (A.end()) break;
        S.push(v);
        G.remove(Edge(v, w));
        v = w;
      }
    return v;
  }
template <class Graph>
void ePATH<Graph>::show()
    { 
      if (!found) return;
      while (tour(v) == v && !S.empty())
        { v = S.pop(); cout << "-" << v; }
      cout << endl;    
    }

----------
CHAPTER 18. Graph Search
-----
#include <vector>
template <class Graph> class cDFS
{ int cnt;
  const Graph &G;
  vector <int> ord; 
  void searchC(int v)
    { 
      ord[v] = cnt++;
      typename Graph::adjIterator A(G, v);
      for (int t = A.beg(); !A.end(); t = A.nxt()) 
        if (ord[t] == -1) searchC(t);
    }
public:
  cDFS(const Graph &G, int v = 0) : 
    G(G), cnt(0), ord(G.V(), -1) 
    { searchC(v); }
  int count() const { return cnt; }
  int operator[](int v) const { return ord[v]; }
};
-----
template <class Graph> class SEARCH
{
  protected:
    const Graph &G;
    int cnt;
    vector <int> ord;
    virtual void searchC(Edge) = 0;
    void search()
      { for (int v = 0; v < G.V(); v++)
          if (ord[v] == -1) searchC(Edge(v, v)); }
  public:
    SEARCH (const Graph &G) : G(G), 
      ord(G.V(), -1), cnt(0) { }
    int operator[](int v) const { return ord[v]; }
};
-----
template <class Graph> 
class DFS : public SEARCH<Graph> 
{ vector<int> st;
  void searchC(Edge e)
    { int w = e.w; 
      ord[w] = cnt++; st[e.w] = e.v;
      typename Graph::adjIterator A(G, w);
      for (int t = A.beg(); !A.end(); t = A.nxt()) 
        if (ord[t] == -1) searchC(Edge(w, t));
    }
public:
  DFS(const Graph &G) : SEARCH<Graph>(G), 
    st(G.V(), -1) { search(); } 
  int ST(int v) const { return st[v]; }
};
-----
template <class Graph> class CC
{ const Graph &G;
  int ccnt;
  vector <int> id; 
  void ccR(int w)
    { 
      id[w] = ccnt;
      typename Graph::adjIterator A(G, w);
      for (int v = A.beg(); !A.end(); v = A.nxt()) 
        if (id[v] == -1) ccR(v);
    }
public:
  CC(const Graph &G) : G(G), ccnt(0), id(G.V(), -1) 
    { 
      for (int v = 0; v < G.V(); v++)
        if (id[v] == -1) { ccR(v); ccnt++; } 
    }
  int count() const { return ccnt; }
  bool connect(int s, int t) const 
    { return id[s] == id[t]; }
};
-----
template <class Graph> 
class EULER : public SEARCH<Graph> 
{ 
  void searchC(Edge e)
  { int v = e.v, w = e.w;
    ord[w] = cnt++;
    cout << "-" << w; 
    typename Graph::adjIterator A(G, w);
    for (int t = A.beg(); !A.end(); t = A.nxt()) 
      if (ord[t] == -1) searchC(Edge(w, t));
      else if (ord[t] < ord[v])
        cout << "-" << t << "-" << w;
    if (v != w) cout << "-" << v; else cout << endl;  
  }
public:
  EULER(const Graph &G) : SEARCH<Graph>(G) 
    { search(); }
};

-----
template <class Graph> class BI
{ const Graph &G;
  bool OK;
  vector <int> vc; 
  bool dfsR(int v, int c)
    { 
      vc[v] = (c+1) %2;
      typename Graph::adjIterator A(G, v);
      for (int t = A.beg(); !A.end(); t = A.nxt()) 
        if (vc[t] == -1) 
          { if (!dfsR(t, vc[v])) return false; } 
        else if (vc[t] != c) return false;
      return true;
    }
public:
  BI(const Graph &G) : G(G), OK(true), vc(G.V(),-1) 
    { 
      for (int v = 0; v < G.V(); v++)
        if (vc[v] == -1) 
          if (!dfsR(v, 0)) { OK = false; return; }
    }
  bool bipartite() const { return OK; }
  int color(int v) const { return vc[v]; }
};
-----
template <class Graph> 
class EC : public SEARCH<Graph> 
{ int bcnt;
  vector <int> low; 
  void searchC(Edge e)
  { int w = e.w;
    ord[w] = cnt++; low[w] = ord[w];
    typename Graph::adjIterator A(G, w);
    for (int t = A.beg(); !A.end(); t = A.nxt()) 
      if (ord[t] == -1) 
        {
          searchC(Edge(w, t));
          if (low[w] > low[t]) low[w] = low[t];
          if (low[t] == ord[t]) 
            bcnt++; // w-t is a bridge
        }
      else if (t != e.v)
        if (low[w] > ord[t]) low[w] = ord[t];
  }
public:
  EC(const Graph &G) : SEARCH<Graph>(G), 
    bcnt(0), low(G.V(), -1)
    { search(); }
  int count() const { return bcnt+1; }
};
-----
#include "QUEUE.cc"
template <class Graph> 
class BFS : public SEARCH<Graph> 
{ vector<int> st;
  void searchC(Edge e)
  { QUEUE<Edge> Q;  
    Q.put(e);
    while (!Q.empty())
      if (ord[(e = Q.get()).w] == -1) 
      { int v = e.v, w = e.w;
        ord[w] = cnt++; st[w] = v;        
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) 
          if (ord[t] == -1) Q.put(Edge(w, t));
      }
  }
public:
  BFS(Graph &G) : SEARCH<Graph>(G), st(G.V(), -1) 
    { search(); }
  int ST(int v) const { return st[v]; }
};
-----
  void searchC(Edge e)
  { QUEUE<Edge> Q;
    Q.put(e); ord[e.w] = cnt++; 
    while (!Q.empty())
      {
        e = Q.get(); st[e.w] = e.v;        
        typename Graph::adjIterator A(G, e.w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) 
          if (ord[t] == -1) 
            { Q.put(Edge(e.w, t)); ord[t] = cnt++; }
      }
  }
-----
#include "GQ.cc"
template <class Graph>
class PFS : public SEARCH<Graph> 
{ vector<int> st;
  void searchC(Edge e)
  { GQ<Edge> Q(G.V());
    Q.put(e); ord[e.w] = cnt++; 
    while (!Q.empty()) 
      {
        e = Q.get(); st[e.w] = e.v;        
        typename Graph::adjIterator A(G, e.w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) 
          if (ord[t] == -1)
            { Q.put(Edge(e.w, t)); ord[t] = cnt++; }
          else 
            if (st[t] == -1) Q.update(Edge(e.w, t));
      }
  }
public:
  PFS(Graph &G) : SEARCH<Graph>(G), st(G.V(), -1)
    { search(); }
  int ST(int v) const { return st[v]; }
};

-----
template <class Item>
class GQ
  {
    private:
      vector<Item> s; int N;
    public:
      GQ(int maxN) : s(maxN+1), N(0) { }
      int empty() const
        { return N == 0; }
      void put(Item item)
        { s[N++] = item; }
      void update(Item x) { }
      Item get()
        { int i = int(N*rand()/(1.0+RAND_MAX));
          Item t = s[i];
          s[i] = s[N-1];
          s[N-1] = t;
          return s[--N]; }
  };

----------
CHAPTER 19. Digraphs and DAGs
-----
template <class inGraph, class outGraph> 
void reverse(const inGraph &G, outGraph &R)
  { 
    for (int v = 0; v < G.V(); v++) 
      { typename inGraph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()) 
          R.insert(Edge(w, v));
      }
  }
-----
template <class Graph> class DFS
{ const Graph &G;
  int depth, cnt, cntP;
  vector<int> pre, post;
  void show(char *s, Edge e)
    { for (int i = 0; i < depth; i++) cout << "  ";
      cout << e.v << "-" << e.w << s << endl; }
  void dfsR(Edge e)
    { int w = e.w; show(" tree", e);
      pre[w] = cnt++; depth++;
      typename Graph::adjIterator A(G, w);
      for (int t = A.beg(); !A.end(); t = A.nxt())
      { Edge x(w, t);
        if (pre[t] == -1) dfsR(x);
        else if (post[t] == -1) show(" back", x);
        else if (pre[t] > pre[w]) show(" down", x);
        else show(" cross", x);
      }
      post[w] = cntP++; depth--;
    }
public:
  DFS(const Graph &G) : G(G), cnt(0), cntP(0), 
    pre(G.V(), -1), post(G.V(), -1)
    { for (int v = 0; v < G.V(); v++) 
        if (pre[v] == -1) dfsR(Edge(v, v)); }
};
-----
template <class tcGraph, class Graph> class TC 
{ tcGraph T;
public:
  TC(const Graph &G) : T(G) 
    { 
      for (int s = 0; s < T.V(); s++) 
        T.insert(Edge(s, s));
      for (int i = 0; i < T.V(); i++)
        for (int s = 0; s < T.V(); s++)
          if (T.edge(s, i))
            for (int t = 0; t < T.V(); t++)
              if (T.edge(i, t))
                T.insert(Edge(s, t));
    }
  bool reachable(int s, int t) const
    { return T.edge(s, t); }
};
-----
template <class Graph> class tc 
{ Graph T; const Graph &G;
  void tcR(int v, int w)
  { 
    T.insert(Edge(v, w));
    typename Graph::adjIterator A(G, w);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      if (!T.edge(v, t)) tcR(v, t);
  }
public:
  tc(const Graph &G) : G(G), T(G.V(), true)
    { for (int v = 0; v < G.V(); v++) tcR(v, v); }
  bool reachable(int v, int w)
    { return T.edge(v, w); }
};
-----
int compressR(link h)
  { STx st;
    if (h == NULL) return 0;
    l = compressR(h->l); 
    r = compressR(h->r);
    t = st.index(l, r);
    adj[t].l = l; adj[t].r = r;
    return t;
  }
-----
template <class Dag> class dagTS 
{ const Dag &D;
  int cnt, tcnt;
  vector<int> pre, post, postI;
  void tsR(int v)
    { 
      pre[v] = cnt++;
      typename Dag::adjIterator A(D, v);
      for (int t = A.beg(); !A.end(); t = A.nxt()) 
        if (pre[t] == -1) tsR(t);
      post[v] = tcnt; postI[tcnt++] = v;
    }
public:
  dagTS(const Dag &D) : D(D), tcnt(0), cnt(0),
   pre(D.V(), -1), post(D.V(), -1), postI(D.V(), -1)
    { for (int v = 0; v < D.V(); v++)
        if (pre[v] == -1) tsR(v); }
  int operator[](int v) const { return postI[v]; }
  int relabel(int v) const { return post[v]; }
};
-----
  void tsR(int v)
    { 
      pre[v] = cnt++;
      for (int w = 0; w < D.V(); w++)
        if (D.edge(w, v))
          if (pre[w] == -1) tsR(w);
      post[v] = tcnt; postI[tcnt++] = v;
    }
-----
#include "QUEUE.cc"
template <class Dag> class dagTS
{ const Dag &D;
  vector<int> in, ts, tsI;
public:
  dagTS(const Dag &D) : D(D), 
    in(D.V(), 0), ts(D.V(), -1), tsI(D.V(), -1) 
  { QUEUE<int> Q;
    for (int v = 0; v < D.V(); v++) 
      {
        typename Dag::adjIterator A(D, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) 
          in[t]++;
      }
    for (int v = 0; v < D.V(); v++)
      if (in[v] == 0) Q.put(v);
    for (int j = 0; !Q.empty(); j++) 
      {
        ts[j] = Q.get(); tsI[ts[j]] = j;
        typename Dag::adjIterator A(D, ts[j]);
        for (int t = A.beg(); !A.end(); t = A.nxt()) 
          if (--in[t] == 0) Q.put(t);
      }
  }
  int operator[](int v) const { return ts[v]; }
  int relabel(int v) const { return tsI[v]; }
};
-----
template <class tcDag, class Dag> class dagTC
{ tcDag T; const Dag &D;
  int cnt;
  vector<int> pre;
  void tcR(int w)
  { 
    pre[w] = cnt++;
    typename Dag::adjIterator A(D, w);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      { 
        T.insert(Edge(w, t));
        if (pre[t] > pre[w]) continue;
        if (pre[t] == -1) tcR(t);
        for (int i = 0; i < T.V(); i++)
          if (T.edge(t, i)) T.insert(Edge(w, i));
      }
  }
public:
  dagTC(const Dag &D) : D(D), cnt(0), 
    pre(D.V(), -1), T(D.V(), true)
    { for (int v = 0; v < D.V(); v++) 
       if (pre[v] == -1) tcR(v); }
  bool reachable(int v, int w) const 
    { return T.edge(v, w); }
};
-----
template <class Graph> class SC 
{ const Graph &G;
  int cnt, scnt;
  vector<int> postI, postR, id;
  void dfsR(const Graph &G, int w)
  { 
    id[w] = scnt;
    typename Graph::adjIterator A(G, w);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      if (id[t] == -1) dfsR(G, t);
    postI[cnt++] = w;
  }
public:
  SC(const Graph &G) : G(G), cnt(0), scnt(0), 
    postI(G.V()), postR(G.V()), id(G.V(), -1)
    { Graph R(G.V(), true);
      reverse(G, R);
      for (int v = 0; v < R.V(); v++)
        if (id[v] == -1) dfsR(R, v);
      postR = postI; cnt = scnt = 0;
      id.assign(G.V(), -1);
      for (int v = G.V()-1; v >= 0; v--)
        if (id[postR[v]] == -1)
          { dfsR(G, postR[v]); scnt++; }
    }
  int count() const { return scnt; }
  bool stronglyreachable(int v, int w) const 
    { return id[v] == id[w]; }
};
-----
#include "STACK.cc"
template <class Graph> class SC 
{ const Graph &G;
  STACK<int> S;
  int cnt, scnt;
  vector<int> pre, low, id;
  void scR(int w)
  { int t; 
    int min = low[w] = pre[w] = cnt++;
    S.push(w);
    typename Graph::adjIterator A(G, w);
    for (t = A.beg(); !A.end(); t = A.nxt())
      { 
        if (pre[t] == -1) scR(t);
        if (low[t] < min) min = low[t]; 
      }
    if (min < low[w]) { low[w] = min; return; }
    do 
      { id[t = S.pop()] = scnt; low[t] = G.V(); }
    while (t != w);
    scnt++;
  }
public:
  SC(const Graph &G) : G(G), cnt(0), scnt(0), 
    pre(G.V(), -1), low(G.V()), id(G.V())
    { for (int v = 0; v < G.V(); v++) 
        if (pre[v] == -1) scR(v); }
  int count() const { return scnt; }
  bool stronglyreachable(int v, int w) const 
    { return id[v] == id[w]; }
};
-----
  void scR(int w)
  { int v;
    pre[w] = cnt++;
    S.push(w); path.push(w);
    typename Graph::adjIterator A(G, w);
    for (int t = A.beg(); !A.end(); t = A.nxt())
      if (pre[t] == -1) scR(t);
      else if (id[t] == -1) 
        while (pre[path.top()] > pre[t]) path.pop();
    if (path.top() == w) path.pop(); else return;
    do { id[v = S.pop()] = scnt; } while (v != w);
    scnt++;
  }
-----
template <class Graph> class TC 
{ const Graph &G; DenseGRAPH *K;
  dagTC<DenseGRAPH, Graph> *Ktc;
  SC<Graph> *Gsc;
public:
  TC(const Graph &G) : G(G)
    { 
      Gsc = new SC<Graph>(G); 
      K = new DenseGRAPH(Gsc->count(), true);
      for (int v = 0; v < G.V(); v++) 
      { typename Graph::adjIterator A(G, v);
        for (int t = A.beg(); !A.end(); t = A.nxt())
          K->insert(Edge(Gsc->ID(v), Gsc->ID(t))); }
      Ktc = new dagTC<DenseGRAPH, Graph>(*K);
    }
  ~TC() { delete K; delete Ktc; delete Gsc; }
  bool reachable(int v, int w)
  { return Ktc->reachable(Gsc->ID(v), Gsc->ID(w));}
};

----------
CHAPTER 20. Minimum Spanning Trees
-----
class EDGE
  { 
    public:
      EDGE(int, int, double);
      int v() const;
      int w() const;
      double wt() const;
      bool from(int) const;
      int other(int) const;
  };
template <class Edge> class GRAPH
  {
    public:
      GRAPH(int, bool);
      ~GRAPH();
      int V() const;
      int E() const;
      bool directed() const;
      int insert(Edge *);
      int remove(Edge *);
      Edge *edge(int, int);
      class adjIterator
        {
          public:
            adjIterator(const GRAPH &, int);
            Edge *beg();
            Edge *nxt();
            bool end();
        };
  };
-----
template <class Graph, class Edge> 
vector <Edge *> edges(const Graph &G)
{ int E = 0;
  vector <Edge *> a(G.E()); 
  for (int v = 0; v < G.V(); v++) 
    {
      typename Graph::adjIterator A(G, v);
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        if (e->from(v)) a[E++] = e;
    }
  return a;
}
-----
template <class Edge> class DenseGRAPH
{ int Vcnt, Ecnt; bool digraph;
  vector <vector <Edge *> > adj;
public:
  DenseGRAPH(int V, bool digraph = false) :
    adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
    { 
      for (int i = 0; i < V; i++) 
        adj[i].assign(V, 0);
    }
  int V() const { return Vcnt; }
  int E() const { return Ecnt; }
  bool directed() const { return digraph; }
  void insert(Edge *e)
    { int v = e->v(), w = e->w();
      if (adj[v][w] == 0) Ecnt++;
      adj[v][w] = e;
      if (!digraph) adj[w][v] = e;
    } 
  void remove(Edge *e)
    { int v = e->v(), w = e->w();
      if (adj[v][w] != 0) Ecnt--;
      adj[v][w] = 0;
      if (!digraph) adj[w][v] = 0; 
    } 
  Edge* edge(int v, int w) const 
    { return adj[v][w]; }
  class adjIterator;
  friend class adjIterator;
};
-----
template <class Edge>
class DenseGRAPH<Edge>::adjIterator
{ const DenseGRAPH<Edge> &G;
  int i, v;
public:
  adjIterator(const DenseGRAPH<Edge> &G, int v) : 
    G(G), v(v), i(0) { }
  Edge *beg()
    { i = -1; return nxt(); }
  Edge *nxt()
    {
      for (i++; i < G.V(); i++)
        if (G.edge(v, i)) return G.adj[v][i];
      return 0;
    }
  bool end() const
    { return i >= G.V(); }
};
-----
template <class Edge> class SparseMultiGRAPH
{ int Vcnt, Ecnt; bool digraph;
  struct node
    { Edge* e; node* next;
      node(Edge* e, node* next): e(e), next(next) {}
    };
  typedef node* link;
  vector <link> adj;
public:
  SparseMultiGRAPH(int V, bool digraph = false) :
    adj(V), Vcnt(V), Ecnt(0), digraph(digraph) { }
  int V() const { return Vcnt; }
  int E() const { return Ecnt; }
  bool directed() const { return digraph; }
  void insert(Edge *e)
    { 
      adj[e->v()] = new node(e, adj[e->v()]);
      if (!digraph) 
        adj[e->w()] = new node(e, adj[e->w()]); 
      Ecnt++;
    } 
  class adjIterator;
  friend class adjIterator;
};
-----
template <class Graph, class Edge> class MST
{ const Graph &G;
  vector<double> wt;
  vector<Edge *> fr, mst;
public:
  MST(const Graph &G) : G(G), 
    mst(G.V()), wt(G.V(), G.V()), fr(G.V())
    { int min = -1; 
      for (int v = 0; min != 0; v = min) 
      { 
        min = 0;
        for (int w = 1; w < G.V(); w++) 
          if (mst[w] == 0)
            { double P; Edge* e = G.edge(v, w);
              if (e)
                if ((P = e->wt()) < wt[w])
                  { wt[w] = P; fr[w] = e; }
              if (wt[w] < wt[min]) min = w;
            }
        if (min) mst[min] = fr[min];
      }
    }
  void show() 
  { for (int v = 1; v < G.V(); v++) 
      if (mst[v]) mst[v]->show();} 
};
-----
template <class Graph, class Edge> class MST
{ const Graph &G;
  vector<double> wt;
  vector<Edge *> fr, mst;
  void pfs(int s) 
  { PQi<double> pQ(G.V(), wt);
    pQ.insert(s);
    while (!pQ.empty()) 
    { int v = pQ.getmin(); 
      mst[v] = fr[v];
      typename Graph::adjIterator A(G, v);
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        { double P = e->wt(); int w = e->other(v); 
          if (fr[w] == 0)
            { wt[w] = P; pQ.insert(w); fr[w] = e; }
          else if (mst[w] == 0 && P < wt[w])
            { wt[w] = P; pQ.lower(w); fr[w] = e; }
        }
    }
  }
public:
  MST(Graph &G) : G(G), 
    fr(G.V()), mst(G.V()), wt(G.V(), -1)
    { for (int v = 0; v < G.V(); v++)
        if (mst[v] == 0) pfs(v); }
};
-----
template <class Graph, class Edge, class EdgePtr> 
class MST
{ const Graph &G;
  vector<EdgePtr> a, mst;
  UF uf;
public:
  MST(Graph &G) : G(G), uf(G.V()), mst(G.V())
  { int V = G.V(), E = G.E();
    a = edges<Graph, Edge, EdgePtr>(G);
    sort<EdgePtr>(a, 0, E-1);
    for (int i = 0, k = 1; i < E && k < V; i++)
      if (!uf.find(a[i]->v, a[i]->w)) 
        { uf.unite(a[i]->v, a[i]->w);
          mst[k++] = a[i]; }
  }
};
-----
template <class Graph, class Edge> class MST
{ const Graph &G;
  vector<Edge *> a, b, mst;
  UF uf;
public:
  MST(const Graph &G): G(G), uf(G.V()), mst(G.V()+1)
  { a = edges<Graph, Edge>(G);
    int N, k = 1;
    for (int E = a.size(); E != 0; E = N) 
    { int h, i, j;
      b.assign(G.V(), 0);
      for (h = 0, N = 0; h < E; h++) 
      { Edge *e = a[h];
        i = uf.find(e->v()), j = uf.find(e->w());
        if (i == j) continue;
        if (!b[i] || e->wt() < b[i]->wt()) b[i] = e;
        if (!b[j] || e->wt() < b[j]->wt()) b[j] = e;
        a[N++] = e;
      }
      for (h = 0; h < G.V(); h++) 
       if (b[h])
        if (!uf.find(i = b[h]->v(), j = b[h]->w()))
          { uf.unite(i, j); mst[k++] = b[h]; }
      }
  }
};
-----
template <class keyType> class PQi 
{ int d, N;
  vector<int> pq, qp; 
  const vector<keyType> &a; 
  void exch(int i, int j)
    { int t = pq[i]; pq[i] = pq[j]; pq[j] = t;
      qp[pq[i]] = i; qp[pq[j]] = j; }
  void fixUp(int k)
    { while (k > 1 && a[pq[(k+d-2)/d]] > a[pq[k]])
        { exch(k, (k+d-2)/d); k = (k+d-2)/d; } }
  void fixDown(int k, int N)
    { int j;
      while ((j = d*(k-1)+2) <= N)
        { 
          for (int i = j+1; i < j+d && i <= N; i++)
            if (a[pq[j]] > a[pq[i]]) j = i;
          if (!(a[pq[k]] > a[pq[j]])) break;
          exch(k, j); k = j;
        }
    }
public:
  PQi(int N, const vector<keyType> &a, int d = 3) : 
    a(a), pq(N+1, 0), qp(N+1, 0), N(0), d(d) { }
  int empty() const { return N == 0; }
  void insert(int v) 
    { pq[++N] = v; qp[v] = N; fixUp(N); }
  int getmin()
    { exch(1, N); fixDown(1, N-1); return pq[N--]; }
  void lower(int k)
    { fixUp(qp[k]); }
};

----------
CHAPTER 21. Shortest Paths
-----
 template <class Graph, class Edge> class SPT
{ const Graph &G;
  vector<double> wt;
  vector<Edge *> spt;
public:
  SPT(const Graph &G, int s) : G(G), 
    spt(G.V()), wt(G.V(), G.V())
  { PQi<double> pQ(G.V(), wt);
    for (int v = 0; v < G.V(); v++) pQ.insert(v);
    wt[s] = 0.0; pQ.lower(s);  
    while (!pQ.empty()) 
    { int v = pQ.getmin(); // wt[v] = 0.0;
      if (v != s && spt[v] == 0) return;  
      typename Graph::adjIterator A(G, v); 
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        { int w = e->w(); 
          double P = wt[v] + e->wt();
          if (P < wt[w]) 
            { wt[w] = P; pQ.lower(w); spt[w] = e; }
        }
    }
  }
  Edge *pathR(int v) const { return spt[v]; }
  double dist(int v) const { return wt[v]; }
};
-----
template <class Graph, class Edge> class SPall
{
  public:
    SPall(const Graph &);
    Edge *path(int, int) const;
    Edge *pathR(int, int) const;
    double dist(int, int) const;
};
-----
template <class Graph, class Edge>
double diameter(Graph &G)
{ int vmax = 0, wmax = 0;
  allSP<Graph, Edge> all(G);
  for (int v = 0; v < G.V(); v++)
    for (int w = 0; w < G.V(); w++)
      if (all.path(v, w))
        if (all.dist(v, w) > all.dist(vmax, wmax))
          { vmax = v; wmax = w; }
  int v = vmax; cout << v;
  while (v != wmax) 
   { v = all.path(v, wmax)->w(); cout << "-" << v; }
  return all.dist(vmax, wmax);
}
-----
#include "SPT.cc"
template <class Graph, class Edge> class allSP
{ const Graph &G;
  vector< SPT<Graph, Edge> *> A;
public:
  allSP(const Graph &G) : G(G), A(G.V())
    { for (int s = 0; s < G.V(); s++) 
        A[s] = new SPT<Graph, Edge>(G, s); }
  Edge *pathR(int s, int t) const
    { return A[s]->pathR(t); }
  double dist(int s, int t) const
    { return A[s]->dist(t); }
};
-----
template <class Graph, class Edge> class allSP 
{ const Graph &G;
  vector <vector <Edge *> > p;
  vector <vector <double> > d;
public:
  allSP(const Graph &G) : G(G), p(G.V()), d(G.V())
    { int V = G.V(); 
      for (int i = 0; i < V; i++) 
        { p[i].assign(V, 0); d[i].assign(V, V); }
      for (int s = 0; s < V; s++)
        for (int t = 0; t < V; t++) 
          if (G.edge(s, t))
            { p[s][t] = G.edge(s, t); 
              d[s][t] = G.edge(s, t)->wt(); } 
      for (int s = 0; s < V; s++) d[s][s] = 0;
      for (int i = 0; i < V; i++)
        for (int s = 0; s < V; s++)
          if (p[s][i])
            for (int t = 0; t < V; t++)
              if (s != t) 
                if (d[s][t] > d[s][i] + d[i][t])
                  { p[s][t] = p[s][i];
                    d[s][t] = d[s][i] + d[i][t]; }
    }
  Edge *path(int s, int t) const
    { return p[s][t]; }
  double dist(int s, int t) const
    { return d[s][t]; }
};
-----
#include "dagTS.cc"
template <class Graph, class Edge> class LPTdag
{ const Graph &G;
  vector<double> wt;
  vector<Edge *> lpt;
public:
  LPTdag(const Graph &G) : G(G), 
    lpt(G.V()), wt(G.V(), 0)
  { int j, w;
    dagTS<Graph> ts(G);
    for (int v = ts[j = 0]; j < G.V(); v = ts[++j]) 
    { typename Graph::adjIterator A(G, v);
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        if (wt[w = e->w()] < wt[v] + e->wt())
          { wt[w] = wt[v] + e->wt(); lpt[w] = e; }
    }
  }
  Edge *pathR(int v) const { return lpt[v]; }
  double dist(int v) const { return wt[v]; }
};
-----
template <class Graph, class Edge> class allSPdag 
{ const Graph &G;
  vector <vector <Edge *> > p;
  vector <vector <double> > d;
  void dfsR(int s) 
  { typename Graph::adjIterator A(G, s); 
    for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
    { int t = e->w(); double w = e->wt();
      if (d[s][t] > w)
        { d[s][t] = w; p[s][t] = e; }
      if (p[t][t] == 0) dfsR(t);
      for (int i = 0; i < G.V(); i++)
        if (p[t][i])
          if (d[s][i] > w + d[t][i])
            { d[s][i] = w + d[t][i]; p[s][i] = e; }
    }
  }
public:
  allSPdag(const Graph &G) : G(G), 
    p(G.V()), d(G.V())
  { int V = G.V(); 
    for (int i = 0; i < V; i++) 
      { p[i].assign(V, 0); d[i].assign(V, V); }
    for (int s = 0; s < V; s++)
      if (p[s][s] == 0) dfsR(s);
  }
  Edge *path(int s, int t) const 
    { return p[s][t]; }
  double dist(int s, int t) const 
    { return d[s][t]; }
};
-----
#include "GRAPHbasic.cc"
#include "GRAPHio.cc"
#include "LPTdag.cc"
typedef WeightedEdge EDGE;
typedef DenseGRAPH<EDGE> GRAPH;
int main(int argc, char *argv[])
  { int i, s, t, N = atoi(argv[1]);
    double duration[N];
    GRAPH G(N, true);
    for (int i = 0; i < N; i++) 
      cin >> duration[i];
    while (cin >> s >> t) 
      G.insert(new EDGE(s, t, duration[s]));
    LPTdag<GRAPH, EDGE> lpt(G);
    for (i = 0; i < N; i++)
      cout << i << " " << lpt.dist(i) << endl;
  }
-----
  SPT(Graph &G, int s) : G(G), 
    spt(G.V()), wt(G.V(), G.V())
  { QUEUE<int> Q; int N = 0;
    wt[s] = 0.0; 
    Q.put(s); Q.put(G.V());
    while (!Q.empty())
    { int v;
      while ((v = Q.get()) == G.V()) 
        { if (N++ > G.V()) return; Q.put(G.V()); }
      typename Graph::adjIterator A(G, v); 
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        { int w = e->w(); 
          double P = wt[v] + e->wt();
          if (P < wt[w])
            { wt[w] = P; Q.put(w); spt[w] = e; }
        }
    }
  }

----------
CHAPTER 22. Network Flow
-----
template <class Graph, class Edge> class check
{
 public:
  static int flow(Graph &G, int v) 
    { int x = 0;
      typename Graph::adjIterator A(G, v);
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        x += e->from(v) ? e->flow() : -e->flow();
      return x; 
    }
  static bool flow(Graph &G, int s, int t) 
    { 
      for (int v = 0; v < G.V(); v++)
        if ((v != s) && (v != t))
          if (flow(G, v) != 0) return false;
      int sflow = flow(G, s);
      if (sflow < 0) return false;
      if (sflow + flow(G, t) != 0) return false;
      return true; 
    }    
};
-----
class EDGE
{ int pv, pw, pcap, pflow;
public:
  EDGE(int v, int w, int cap) :
      pv(v), pw(w), pcap(cap), pflow(0) { }
  int v() const { return pv; }
  int w() const { return pw; }
  int cap() const { return pcap; }
  int flow() const { return pflow; }
  bool from (int v) const 
    { return pv == v; } 
  int other(int v) const 
    { return from(v) ? pw : pv; } 
  int capRto(int v) const
    { return from(v) ? pflow : pcap - pflow; }
  void addflowRto(int v, int d) 
    { pflow += from(v) ? -d : d; }
};
-----
template <class Graph, class Edge> class MAXFLOW
{ const Graph &G;
  int s, t;
  vector<int> wt;
  vector<Edge *> st;
  int ST(int v) const { return st[v]->other(v); }
  void augment(int s, int t)
    { int d = st[t]->capRto(t);
      for (int v = ST(t); v != s; v = ST(v))
        if (st[v]->capRto(v) < d) 
          d = st[v]->capRto(v);
      st[t]->addflowRto(t, d); 
      for (int v = ST(t); v != s; v = ST(v))
        st[v]->addflowRto(v, d); 
    }
  bool pfs();
public:
  MAXFLOW(const Graph &G, int s, int t) : G(G),
    s(s), t(t), st(G.V()), wt(G.V())
  { while (pfs()) augment(s, t); }
};
-----
template <class Graph, class Edge>
bool MAXFLOW<Graph, Edge>::pfs()
  { PQi<int> pQ(G.V(), wt);
    for (int v = 0; v < G.V(); v++) 
      { wt[v] = 0; st[v] = 0; pQ.insert(v); }
    wt[s] = -M; pQ.lower(s);  
    while (!pQ.empty()) 
    { int v = pQ.getmin(); wt[v] = -M; 
      if (v == t || (v != s && st[v] == 0)) break;  
      typename Graph::adjIterator A(G, v); 
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        { int w = e->other(v);
          int cap = e->capRto(w);
          int P = cap < -wt[v] ? cap : -wt[v];
          if (cap > 0 && -P < wt[w]) 
            { wt[w] = -P; pQ.lower(w); st[w] = e; }
        }
    }
    return st[t] != 0;
  }
-----
template <class Graph, class Edge> class MAXFLOW
{ const Graph &G;
  int s, t;
  vector<int> h, wt;
  void initheights();
public:
  MAXFLOW(const Graph &G, int s, int t) : G(G),
    s(s), t(t), h(G.V()), wt(G.V(), 0)
  { initheights();
    GQ gQ(G.V());
    gQ.put(s); wt[t] = -(wt[s] = M*G.V());
    while (!gQ.empty()) 
    { int v = gQ.get();
      typename Graph::adjIterator A(G, v); 
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        { int w = e->other(v); 
          int cap = e->capRto(w);
          int P = cap < wt[v] ? cap : wt[v];
          if (P > 0 && v == s || h[v] == h[w]+1) 
            { e->addflowRto(w, P); 
              wt[v] -= P; wt[w] += P;
              if ((w != s) && (w != t)) gQ.put(w); }
        }
      if (v != s && v != t && wt[v] > 0)
        { h[v]++; gQ.put(v); }
    }
  }
};
-----
#include "MAXFLOW.cc"
template <class Graph, class Edge> class FEASIBLE
{ const Graph &G;
  void freeedges(const Graph &F, int v)
   { typename Graph::adjIterator A(F, v);
     for (EDGE* e = A.beg(); !A.end(); e = A.nxt())
       delete e;
   }
public:
  FEASIBLE(const Graph &G, vector<int> sd) : G(G)
  { 
    Graph F(G.V()+2);
    for (int v = 0; v < G.V(); v++) 
    {
      typename Graph::adjIterator A(G, v);
      for (EDGE* e = A.beg(); !A.end(); e = A.nxt())
        F.insert(e);
    }    
    int s = G.V(), t = G.V()+1;
    for (int i = 0; i < G.V(); i++)
      if (sd[i] >= 0)
        F.insert(new EDGE(s, i, sd[i]));
      else
        F.insert(new EDGE(i, t, -sd[i]));
    MAXFLOW<Graph, Edge>(F, s, t);
    freeedges(F, s); freeedges(F, t);
  }
};
-----
#include "GRAPHbasic.cc"
#include "MAXFLOW.cc"
int main(int argc, char *argv[])
{ int s, t, N = atoi(argv[1]);
  GRAPH<EDGE> G(2*N+2);
  for (int i = 0; i < N; i++)
    G.insert(new EDGE(2*N, i, 1));
  while (cin >> s >> t) 
    G.insert(new EDGE(s, t, 1));
  for (int i = N; i < 2*N; i++)
    G.insert(new EDGE(i, 2*N+1, 1));
  MAXFLOW<GRAPH<EDGE>, EDGE>(G, 2*N, 2*N+1);
  for (int i = 0; i < N; i++)
    {
      GRAPH<EDGE>::adjIterator A(G, i);
      for (EDGE* e = A.beg(); !A.end(); e = A.nxt()) 
        if (e->flow() == 1 &&  e->from(i))
        cout << e->v() << "-" << e->w() << endl;
    }
        
}
-----
static int cost(Graph &G)
{ int x = 0;
  for (int v = 0; v < G.V(); v++) 
    { 
      typename Graph::adjIterator A(G, v);
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        if (e->from(v) && e->costRto(e->w()) < C)
          x += e->flow()*e->costRto(e->w()); 
    }
  return x; 
}
-----
template <class Graph, class Edge> class MINCOST
{ const Graph &G;
  int s, t;
  vector<int> wt;
  vector <Edge *> st;
  int ST(int v) const;
  void augment(int, int);
  int negcyc(int);
  int negcyc();
public:
  MINCOST(const Graph &G, int s, int t) : G(G),
    s(s), t(t), st(G.V()), wt(G.V())
  { MAXFLOW<Graph, Edge>(G, s, t);
    for (int x = negcyc(); x != -1; x = negcyc())
      { augment(x, x); }
  }
};
-----
  int phiR(int v) 
    { 
      if (mark[v] == valid) return phi[v];
      phi[v] = phiR(ST(v)) - st[v]->costRto(v);
      mark[v] = valid;
      return phi[v]; 
    }
-----
int lca(int v, int w) 
  { mark[v] = ++valid; mark[w] = valid;
    while (v != w)
      { 
        if (v != t) v = ST(v);
        if (v != t && mark[v] == valid) return v;
        mark[v] = valid;
        if (w != t) w = ST(w); 
        if (w != t && mark[w] == valid) return w;
        mark[w] = valid; 
      }
    return v; 
  }
Edge *augment(Edge *x)
  { int v = x->v(), w = x->w(); int r = lca(v, w);
    int d = x->capRto(w);
    for (int u = w; u != r; u = ST(u))
      if (st[u]->capRto(ST(u)) < d) 
        d = st[u]->capRto(ST(u));
    for (int u = v; u != r; u = ST(u))
      if (st[u]->capRto(u) < d) 
        d = st[u]->capRto(u);
    x->addflowRto(w, d); Edge* e = x;
    for (int u = w; u != r; u = ST(u))
      { st[u]->addflowRto(ST(u), d); 
        if (st[u]->capRto(ST(u)) == 0) e = st[u]; }
    for (int u = v; u != r; u = ST(u))
      { st[u]->addflowRto(u, d); 
        if (st[u]->capRto(u) == 0) e = st[u]; }
    return e;
  }
-----
  bool onpath(int a, int b, int c)
    { 
      for (int i = a; i != c; i = ST(i))
        if (i == b) return true;
      return false; 
    }
  void reverse(int u, int x)
    { Edge *e = st[u];
      for (int i = ST(u); i != x; i = ST(i))
        { Edge *y = st[i]; st[i] = e; e = y; } 
    }
  void update(Edge *w, Edge *y) 
    { int u = y->w(), v = y->v(), x = w->w();
      if (st[x] != w) x = w->v(); 
      int r = lca(u, v);
      if (onpath(u, x, r))
        { reverse(u, x); st[u] = y; return; }
      if (onpath(v, x, r))
        { reverse(v, x); st[v] = y; return; } 
    }
-----
int costR(Edge *e, int v)
  { int R = e->cost() + phi[e->w()] - phi[e->v()];
    return  e->from(v) ? R : -R; }
Edge *besteligible()
{ Edge *x = 0;
  for (int v = 0, min = C*G.V(); v < G.V(); v++) 
    {
      typename Graph::adjIterator A(G, v); 
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        if (e->capRto(e->other(v)) > 0) 
          if (e->capRto(v) == 0)
            if (costR(e, v) < min) 
              { x = e; min = costR(e, v); } 
    }
  return x;
}
-----
template <class Graph, class Edge> class MINCOST
{ const Graph &G; int s, t; int valid; 
  vector<Edge *> st; vector<int> mark, phi;
  void dfsR(Edge);
  int ST(int); 
  int phiR(int); 
  int lca(int, int);  Edge *augment(Edge *);
  bool onpath(int, int, int); 
  void reverse(int, int);
  void update(Edge *, Edge *); 
  int costR(Edge *, int); Edge *besteligible();
public:
  MINCOST(Graph &G, int s, int t) : G(G), s(s), t(t) 
    st(G.V()), mark(G.V(), -1), phi(G.V())
  { 
    Edge *z = new EDGE(s, t, M*G.V(), C*G.V());
    G.insert(z);
    z->addflowto(t, z->cap()); 
    dfsR(z);
    for (valid = 1; ; valid++ ) 
      { 
        phi[t] = z->costRto(s); mark[t] = valid; 
        for (int v = 0; v < G.V(); v++) 
          if (v != t) phi[v] = phiR(v);
        Edge *x = besteligible();
        if (costR(x, x->v()) == 0) break;
        update(augment(x), x);
      }
    G.remove(z); delete z;
  }
-----
int old = 0;
for (valid = 1; valid != old; ) 
  {
    old = valid;
    for (int v = 0; v < G.V(); v++) 
    {
      typename Graph::adjIterator A(G, v); 
      for (Edge* e = A.beg(); !A.end(); e = A.nxt()) 
        if (e->capRto(e->other(v)) > 0)
          if (e->capRto(v) == 0)
            { update(augment(e), e); valid++; }
    }
  }
