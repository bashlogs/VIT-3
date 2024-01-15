import java.util.*;
class publication{
    String title;
    float price;

    public void getData(){
        Scanner sc = new Scanner(System.in);
        System.out.print("Title: ");
        title = sc.nextLine();
        System.out.print("Price: ");
        price = sc.nextFloat();
    }
    public void display(){
        System.out.println("Title: " + title);
        System.out.println("Price: " + price);
    }
}

class book extends publication{
    int pageCount;
    public void getData(){
        super.getData();
        Scanner sc = new Scanner(System.in);
        System.out.print("Total Pages: ");
        pageCount = sc.nextInt();
    }
    public void display(){
        super.display();
        System.out.println("Page count: " + pageCount);
    }
}

class tape extends publication{

    int playTime;

    public void getData(){
        super.getData();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Total Playtime (Min): ");
        playTime = scanner.nextInt();
    }

    public void display(){
        super.display();
        System.out.println("Play time: " + playTime + "m");
    }
}

class books{
    public static void main(String[] args) {
        book b1 = new book();
        tape t1 = new tape();

        System.out.println("Enter book details");
        b1.getData();

        System.out.println("\nEnter tape details:");
        t1.getData();

        System.out.println("\nBook details:");
        b1.display();

        System.out.println("\nTape details:");
        t1.display();
    }
}