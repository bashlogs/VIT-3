
@SpringBootApplication
  
public class SpringBootAppApplication implements CommandLineRunner
{
    @Override
    public void run(String args[]) throws Exception
    {
        System.out.println("HEllo world");
    }
  
    public static void main(String[] args)
    {
        SpringApplication.run(SpringBootAppApplication.class, args);
    }
}