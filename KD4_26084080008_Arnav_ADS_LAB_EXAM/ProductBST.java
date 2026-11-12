package com.sunbeam;

public class ProductBST {
	static class Node {
		private int id;
		private String name;
		private double price;
		private Node left;
		private Node right;
		
		public Node(int id, String name, double price) {
			this.id = id;
			this.name = name;
			this.price = price;
			left = right = null;
		}
		@Override
		public String toString() {
			return String.format("ProductId : %-10d || Product name: %-10s || Product Price: %-6f", id, name, price);
		}
	}
	private Node root;
	public ProductBST() {
		root = null;
	}
	// 1. insert a product price
	public void addNewProduct(int id, String name, double price) {
		Node newNode = new Node(id, name, price);
		if(root==null) {
			root = newNode;
		} else {
			Node trav = root;
			while(trav!=newNode) {
				if(price==trav.price) return; // don't allow duplicate prices
				else if(price>trav.price) {
					if(trav.right==null) {
						trav.right = newNode;
					} else {
						trav = trav.right;
					}
				} else {
					if(trav.left==null) {
						trav.left = newNode;
					} else {
						trav = trav.left;
					}
				}
			}
		}
	}
	
	// 2. delete a product
	public void deleteProduct(double price) {
		Node trav = root;
		Node parent = null;
		// search the target node
		while(trav!=null) {
			if(trav.price == price) 
				break;
			parent = trav;
			if(price > trav.price) 
				trav = trav.right;
			else 
				trav = trav.left;
		}
		if(trav==null) return;
		//case 1: if both the children are present
		if(trav.left!=null && trav.right!=null) {
			Node pred = trav.left;
			parent = trav;
			while(pred.right!=null) {
				parent = pred;
				pred = pred.right;
			}
			trav.price = pred.price;
			trav.name = pred.name;
			trav.id = pred.id;
			if(pred == parent.left) 
				parent.left = pred.left;
			else 
				parent.right = pred.left;	
		} else if(trav.left==null) {
			if(trav==root) 
				root = trav.right;
			else if(trav == parent.left)
				parent.left = trav.right;
			else 
				parent.right = trav.right;
		} else { // trav.right==null
			if(trav==root)
				root = trav.left;
			else if(trav == parent.left)
				parent.left = trav.left;
			else 
				parent.right = trav.right;
		}
	}
	
	// 3. Display all product prices in ascending order
	public void displayBST(Node root) {
		if(root==null) return;
		displayBST(root.left);
		System.out.println(root);
		displayBST(root.right);
	}
	public void displayBST() {
		if(root==null)
			System.out.println("Product BST is empty!!!");
		else {
			System.out.println("Displaying BST in ascending order of price::");
			displayBST(root);
		}
	}
	
	// 4. Search product by price
	public Node searchProduct(double price) {
		Node trav = root;
		while(trav!=null) {
			if(price==trav.price) {
				System.out.println("Product found: " + trav);
				return trav;
			} 
			else if(price > trav.price) 
				trav = trav.right;
			else 
				trav = trav.left;
		}
		return null;
	}
	
	// 5. Count expensive Products
	private void displayExpensiveCount(Node root, double price, int[] count) {
		if(root==null) return;
		displayExpensiveCount(root.left, price, count);
		if(root.price>price) {
			System.out.println(root);
			count[0]++;
		}
		displayExpensiveCount(root.right, price, count);
		
	}
	public void displayExpensiveCount(double price) {
		int[] count = {0};
		System.out.println("Displaying expensive products:: ");
		displayExpensiveCount(root, price, count);
		System.out.println(String.format("Count of products expensive than %f are: %d", price, count[0]));
	}
	
	// 6. Display products in a given range
	private void displayRange(Node root, double low, double high, int[] count) {
		if(root==null) return;
		displayRange(root.left, low, high, count);
		if(root.price>=low && root.price<=high) {
			System.out.println(root);
			count[0]++;
		}
		displayRange(root.right, low, high, count);
		
	}
	public void displayRange(double low, double high) {
		int[] count = {0};
		displayRange(root, low, high, count);
		if(count[0] == 0) {
			System.out.println("Unfortunately no product found in the given range!!!");
			return;
		}
		System.out.println(String.format("Product count: %d", count[0]));
	}
	
	// 7. Find the kth highest product price
	private boolean displayKthHighest(Node root, int[] k, boolean[] flag) {
		if(root==null) return false;
		if(displayKthHighest(root.right, k, flag)) return true;
		if(k[0]==0) {
			System.out.println("Kth highest product: ");
			System.out.println(root);
			return true;
		} 
		k[0]--;
		return displayKthHighest(root.left, k, flag);
	}
	public void displayKthHighest(int k) {
		boolean[] flag = {false};
		int[] count = {k-1};
		if(k>0) displayKthHighest(root, count, flag);
		if(!flag[0]) {
			System.out.println(" Invalid vlaue of k!!!");
		}
	}
}























