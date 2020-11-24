package project3_bfs;

import java.io.*; // for BufferedReader
import java.util.*; // for StringTokenizer
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFileChooser;
import javax.swing.JFrame;

class Edge_Node {
    Vertex_Node target;
    Edge_Node next;

    public Edge_Node(Vertex_Node t, Edge_Node e) {
        target = t;
        next = e;
    }

    public Vertex_Node GetTarget() {
        return target;
    }

    public Edge_Node GetNext() {
        return next;
    }

    Edge_Node sortedMerge(Edge_Node a, Edge_Node b) {
        Edge_Node result = null;
        if (a == null) {
            return b;
        }
        if (b == null) {
            return a;
        }
        if (a.target.name.compareTo(b.target.name) <= 0) {
            result = a;
            result.next = sortedMerge(a.next, b);
        } else {
            result = b;
            result.next = sortedMerge(a, b.next);
        }
        return result;
    }

    Edge_Node mergeSort(Edge_Node h) {
        if (h == null || h.next == null) {
            return h;
        }
        Edge_Node middle = getMiddle(h);
        Edge_Node nextofmiddle = middle.next;
        middle.next = null;
        Edge_Node left = mergeSort(h);
        Edge_Node right = mergeSort(nextofmiddle);
        Edge_Node sortedlist = sortedMerge(left, right);
        return sortedlist;
    }

    Edge_Node sortedMergeDes(Edge_Node a, Edge_Node b) {
        Edge_Node result = null;
        if (a == null) {
            return b;
        }
        if (b == null) {
            return a;
        }
        if (a.target.name.compareTo(b.target.name) > 0) {
            result = a;
            result.next = sortedMergeDes(a.next, b);
        } else {
            result = b;
            result.next = sortedMergeDes(a, b.next);
        }
        return result;
    }

    Edge_Node mergeSortDes(Edge_Node h) {
        if (h == null || h.next == null) {
            return h;
        }
        Edge_Node middle = getMiddle(h);
        Edge_Node nextofmiddle = middle.next;
        middle.next = null;
        Edge_Node left = mergeSortDes(h);
        Edge_Node right = mergeSortDes(nextofmiddle);
        Edge_Node sortedlist = sortedMergeDes(left, right);
        return sortedlist;
    }

    Edge_Node getMiddle(Edge_Node h) {
        if (h == null) {
            return h;
        }
        Edge_Node fastptr = h.next;
        Edge_Node slowptr = h;
        while (fastptr != null) {
            fastptr = fastptr.next;
            if (fastptr != null) {
                slowptr = slowptr.next;
                fastptr = fastptr.next;
            }
        }
        return slowptr;
    }
}

class Vertex_Node {
    String name;
    Edge_Node edge_head;
    int distance;
    Vertex_Node next, parent = null;
    public boolean visited = false;
    String parentName = null;

    public Vertex_Node(String s, Vertex_Node v) {
        name = s;
        next = v;
        distance = -1;
    }

    public String GetName() {
        return name;
    }

    public int GetDistance() {
        return distance;
    }

    public void SetDistance(int d) {
        distance = d;
    }

    public Edge_Node GetNbrList() {
        return edge_head;
    }

    public Vertex_Node GetNext() {
        return next;
    }
}

class Graph {
    Vertex_Node head;
    int size;

    public Graph() {
        head = null;
        size = 0;
    }

    public void clearDist() {
        Vertex_Node pt = head;
        while (pt != null) {
            pt.distance = -1;
            pt = pt.next;
        }
    }

    public Vertex_Node findVertex(String s) {
        Vertex_Node pt = head;
        while (pt != null && s.compareTo(pt.name) != 0) {
            pt = pt.next;
        }
        return pt;
    }

    public Vertex_Node input(String fileName) throws IOException {
        String inputLine, sourceName, targetName;
        Vertex_Node source = null, target;
        Edge_Node e;
        StringTokenizer input;
        BufferedReader inFile = new BufferedReader(new FileReader(fileName));
        inputLine = inFile.readLine();
        while (inputLine != null) {
            input = new StringTokenizer(inputLine);
            sourceName = input.nextToken();
            source = findVertex(sourceName);
            if (source == null) {
                head = new Vertex_Node(sourceName, head);
                source = head;
                size++;
            }
            if (input.hasMoreTokens()) {
                targetName = input.nextToken();
                target = findVertex(targetName);
                if (target == null) {
                    head = new Vertex_Node(targetName, head);
                    target = head;
                    size++;
                }
                // put edge in one direction -- after checking for repeat
                e = source.edge_head;
                while (e != null) {
                    if (e.target == target) {
                        System.out.print("Multiple edges from " + source.name + " to ");
                        System.out.println(target.name + ".");
                        break;
                    }
                    e = e.next;
                }
                source.edge_head = new Edge_Node(target, source.edge_head);
                // put edge in the other direction
                e = target.edge_head;
                while (e != null) {
                    if (e.target == source) {
                        System.out.print("Multiple edges from " + target.name + " to ");
                        System.out.println(source.name + ".");
                        break;
                    }
                    e = e.next;
                }
                target.edge_head = new Edge_Node(source, target.edge_head);
            }
            inputLine = inFile.readLine();
        }
        inFile.close();
        return source;
    }

    public void output() {
        Vertex_Node v = head;
        Edge_Node e;
        while (v != null) {
            System.out.print(v.name + ": ");
            e = v.edge_head;
            while (e != null) {
                System.out.print(e.target.name + " ");
                e = e.next;
            }
            System.out.println();
            v = v.next;
        }
        while (v != null) {
            System.out.print(v.name + ": ");
            e = v.edge_head;
            while (e != null) {
                System.out.print(e.target.name + " ");
                e = e.next;
            }
            System.out.println();
            v = v.next;
        }
        v = head;
        while (v != null) {
            e = v.edge_head;
            v.edge_head = v.edge_head.mergeSort(v.edge_head);
            System.out.println();
            v = v.next;
        }
        this.output_bfs(head);
        while (v != null) {
            e = v.edge_head;
            v.edge_head = v.edge_head.mergeSortDes(v.edge_head);
            System.out.println();
            v = v.next;
        }
        this.output_dfs(head);
    }

    public void output_bfs(Vertex_Node s) {
        LinkedList<Vertex_Node> q = new LinkedList<Vertex_Node>();
        Vertex_Node v = head;
        Edge_Node e;
        while (v.next != null) {
            v.visited = false;
            v = v.GetNext();
        }
        q.add(v);
        v.visited = true;
        System.out.println("BFS: ");
        while (!q.isEmpty()) {
            s = q.poll();
            System.out.print(s.name + " " + s.distance + " " + s.parentName + "\n");
            e = s.edge_head;
            do {
                Vertex_Node eTarget = e.GetTarget();
                if (eTarget.visited != true) {
                    eTarget.visited = true;
                    q.add(eTarget);
                    e.target.parentName = s.name;
                }
                e = e.GetNext();
            } while (e != null);
        }
    }

    public void output_dfs(Vertex_Node s) {
        Stack<Vertex_Node> q = new Stack<Vertex_Node>();
        Vertex_Node v = head;
        Edge_Node e;
        while (v.next != null) {
            v.visited = false;
            v = v.GetNext();
        }
        q.push(v);
        v.visited = true;
        System.out.println("\nDFS: ");
        while (!q.isEmpty()) {
            s = q.pop();
            System.out.print(s.name + " " + s.distance + " " + s.parentName + "\n");
            e = s.edge_head;
            do {
                Vertex_Node eTarget = e.GetTarget();
                if (eTarget.visited != true) {
                    eTarget.visited = true;
                    q.add(eTarget);
                    e.target.parentName = s.name;
                }
                e = e.GetNext();
            } while (e != null);
        }
    }
}

public class Project3_BFS {
    public static void main(String[] args) {
        Graph tempGraph = new Graph();
        JFileChooser chooser = new JFileChooser();
        chooser.setCurrentDirectory(new File("."));
        chooser.setFileFilter(new javax.swing.filechooser.FileFilter() {
            public boolean accept(File f) {
                return f.getName().toLowerCase().endsWith(".txt") || f.isDirectory();
            }

            public String getDescription() {
                return "TXT Images";
            }
        });
        int r = chooser.showOpenDialog(new JFrame());
        if (r == JFileChooser.APPROVE_OPTION) {
            String name = chooser.getSelectedFile().getName();
            System.out.println(name);
        }
        try {
            tempGraph.input(chooser.getSelectedFile().getAbsolutePath());
        } catch (IOException ex) {
            Logger.getLogger(Project3BFS.class.getName()).log(Level.SEVERE, null, ex);
        }
        tempGraph.output();
    }
}