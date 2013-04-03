struct Node {
	std::string data;
	Node* next;
}

class Stack {
	public:
		Stack() {
			top = NULL;
			count = 0;
		}
		  
	  	~Stack() {		
			clear();	 
	     	}
			    		
    		void clear() {
	    		Node *aux;	
				
    			while (top != NULL) {		
				aux = top;			
	    			top = top->next;	
				delete aux;
			}
		 }	        
		
		bool isEmpty(){
			return (top==NULL);
		}
				 			
    		void push(std::string s) {				 
	      		Node *aux = new Node();					
    			aux->data = s;
			aux->next = top;				
			top = aux;		
			count++;							        }
				
		std::string pop() {
			std::string aux;
			Node *tmp = new Node();
			
			if(!isEmpty()) return NULL;				        
			aux = top->data;
			tmp = top;	
		 	top = top->next;
			count--;
			delete tmp;
			return aux;
		}

    		std::string topElement() {            
			return top->data;					
		}
					        
	       int size(){
		       return count;
	       }
					    
	private:
	       int count;
	       Node* top;
};

