import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class Main {
	
	/*
	 * 
	 * Shahzad Ansari 
	 * CS:4365 
	 * Professor Chris Davis
	 * Project 1
	 * 
	 * 
	 * Websites used for reference 
	 * 
	 * https://github.com/jrom/IA/blob/master/srcaima/aima/search/informed/RecursiveBestFirstSearch.java
	 * http://aima.cs.berkeley.edu/python/search.html
	 * 
	 * 
	 */

	public static final int maxlim = Integer.MAX_VALUE;
	
	public static void main(String[] args) {
		
		int []board = new int[9];
		try {
			board = readFromFile();
			
		} catch (FileNotFoundException e) {
						e.printStackTrace();
						System.exit(0);

		}
		
		node root = new node(board);
		root.depth = 0;
		ManhattanDistance h = new ManhattanDistance();
		root.Fcost = h.CalculateHeuristic(root);
		
		SearchResult sr = rBFS(root,maxlim);
		node found = sr.getSolution();
		System.out.println("Solution " + sr.getOutcome());
		if(found != null) 
		{
			found.printPuzzle();
			pathTrace(found);
		}
	}
	
	public static void pathTrace( node n) {
		List<node> traceList = new ArrayList<node>();
		System.out.println("Tracing path");
		System.out.println("The traced path is :");
		node current = n;
		traceList.add(current);
		while(current.parent != null) {
			current = current.parent;
			traceList.add(current);
		}
	System.out.println("-----------------------------");
		for(int i = traceList.size()-1 ; i >= 0 ; i--) {
			traceList.get(i).printPuzzle();
		}
	}

	public static boolean presentInList(node n , List<node> s) {
		for(int i = 0 ; i < s.size();i++) {
			if(samePuzzle(n , s.get(i))) {
				return true;
			}
			
		}
		return false;
	}
	
	public static boolean hasDuplicateParent(node parent , node currentNode) {
		
		if(parent != null) {
			if(samePuzzle(parent, currentNode)) {
				return true;
			}
			return hasDuplicateParent(parent.parent , currentNode);
		}
		else {
			return false;
		}

	}
	
	public static List<node> sortList(List<node> s){
		List<node> tempList = new ArrayList<node>();
		
		node n = new node();
		
		for(int i = 0 ; i < s.size() ; i++) {
			tempList.add(n);
			tempList.get(i).Fcost = 1000000000;
		}
		
		
		int location = 0;
		boolean visited[] = new boolean[s.size()];
		for( int i = 0 ; i < s.size() ; i++) {
			visited[i] = false;
		}
		
		for(int i = 0 ; i < s.size(); i++) {
			for(int j = 0 ; j < s.size() ; j++) {
				if(s.get(j).Fcost < tempList.get(i).Fcost) {
					if(visited[j] == false) {
						tempList.set(i, s.get(j));
						location = j;
					}
				}
				if(j == s.size()-1) {
					visited[location] = true;
				}
			}
		}
		
		
		
		
		return tempList;
		
	}
	
	public static List<node> generateSuccessors(node n , ManhattanDistance h){
		List<node> s = new ArrayList<node>();
		
		for(int i = 0 ; i < n.children.size() ; i++) {
			// loop through all the children and add them to the successors 
			
			node CurrentChild = n.children.get(i);
			CurrentChild.depth = CurrentChild.parent.depth +1;
			CurrentChild.heuristic = h.CalculateHeuristic(CurrentChild);
			CurrentChild.Fcost = CurrentChild.depth + CurrentChild.heuristic;
			if(!hasDuplicateParent(CurrentChild.parent , CurrentChild)) {
				s.add(CurrentChild);
			}
			else {
				
			}
			
		}
		return s;
	}
	
	public static boolean goalTest( node n) {
		int []board = new int[]{0,1,2,3,4,5,6,7,8}; 
		node m = new node(board);
		if(samePuzzle(n , m)) {
			return true;	
		}
		return false;
	}
	           	
	public static int[] readFromFile() throws FileNotFoundException {
		 @SuppressWarnings("resource")
		Scanner scan = new Scanner(new File("puzzle.txt")); //provide file name from outside
	        int counter =0; //keep track of how many integers in the file
	        while(scan.hasNextInt()) 
	        {
	            counter++;
	            scan.nextInt();
	        }
	        @SuppressWarnings("resource")
			Scanner scan2 = new Scanner(new File("puzzle.txt")); 
	        int a[] = new int[counter];
	        for(int i=0;i<counter;i++)
	        {
	            a[i]=scan2.nextInt(); //fill the array with the integers
	        }
		return a;
		
	}
	
	public static boolean samePuzzle(node n , node m) {

		for(int i = 0 ; i < n.puzzle.length ; i++) {
			if(n.accessPuzzle(n.puzzle, i) != m.accessPuzzle(m.puzzle, i)) {
				return false;
			}
		}
		return true;
	}
	
	public static SearchResult rBFS(node n , int limit) {
		List<node> successors = new ArrayList<node>();
		ManhattanDistance h = new ManhattanDistance();

		
		n.printPuzzle();
		System.out.println("n depth is " + n.depth + " n heuristic is " + n.heuristic); 
		if(goalTest(n)) {
			
			System.out.println("goalTest passed : this is the solved puzzle ");
			n.printPuzzle();

			return new SearchResult(n,limit);
		}
		
		n.ExpandMove();
		
		
		successors = generateSuccessors(n , h);
		System.out.println("Created succssors list of size : " + successors.size());
		
		if(0 == successors.size()) {
			System.out.println("found nothing , successors size is zero");
			System.out.println("------ End Call----------");
			return new SearchResult(null, maxlim);
		}
		
		// for each s in successors do
		int size = successors.size();
		for (int s = 0; s < size; s++) {
			// f[s] <- max(g(s) + h(s), f[node])
			successors.get(s).Fcost = Math.max(successors.get(s).Fcost, n.Fcost);
		}
		
		while(true) {
			successors = sortList(successors);
			node best = successors.get(0);
			node alt = successors.size() == 1 ? best: successors.get(1);

			System.out.println("Best Cost = " + best.Fcost+ " Alt Cost = " + alt.Fcost);

			if(best.Fcost > limit) {
				
				System.out.println("found nothing , fcost exceeds limit" + "limit is " + limit + " fcost is "  + best.Fcost);
				System.out.println("------ End Call----------");
				return new SearchResult(null, best.Fcost);
			}

			SearchResult sr = rBFS(best , Math.min(limit,alt.Fcost));

			best.Fcost = sr.getFCostLimit();
			if(sr.getSolution() != null) {
				System.out.println("found fcost is " + sr.getFCostLimit());
				System.out.println("------ End Call----------");
				return sr;
			}

		}

	}
	
}