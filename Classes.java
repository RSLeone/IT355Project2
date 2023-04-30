import java.util.regex.Pattern;
import java.util.regex.Matcher;




class Person implements Cloneable {
    private String name;
    private String ID;
    private String SSN;
    private static Pattern pattern = Pattern.compile("^[0-9]{9}$");


    public Person(String name, String id, String SSN) {
        this.name = name;
        this.ID = id;
        this.SSN = SSN;
    }

    public String toString() {
        return this.name + " " + this.ID; // + " " + this.SSN; --> Part of CWE-492, I don't want to be able to print the
                                          // SSN
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setID(String id) {
        this.ID = id;
    }

    // Avoiding CWE-233: Improper Handling of Parameters
    public void setSSN(String SSN) {
        Matcher matcher = pattern.matcher(SSN);
        if (matcher.matches()) {
            this.SSN = SSN;
        }
        else {
            System.out.println("Invalid SSN");
        }
    }

    // CWE-767: Access to Critical Private Variable via Public Method
    public String getSSN() {
        return this.SSN; // BAD IDEA! Shown for educational purposes
    }

    public String getID() {
        return this.ID;
    }

    public String getName() {
        return this.name;
    }

    @Override
    public Person clone() {
        // try {
        return (Person) this;// super.clone();
        // } catch (CloneNotSupportedException e) {
        // // Should never happen
        // throw new AssertionError();
        // }
    }

    class Student {
        private double gpa;

        public Student(String name, String id, String SSN, double gpa) {
            Person.this.setName(name);
            Person.this.setID(id);
            Person.this.setSSN(SSN);
            this.gpa = gpa;
        }

        public String getSSN() {
            return Person.this.SSN;
        }

        public String toString() {
            return Person.this.toString() + " " + this.gpa;
        }
    }
}

class Employee extends Person {
    private String name;
    private String ID;
    private String SSN;
    private String workId;

    public Employee(String name, String ID, String SSN, String workId) {
        super(name, ID, SSN);
        this.workId = workId;
    }

    @Override
    public Employee clone() {
        // try {

        // CWE-580: clone() Method Without super.clone()
        return (Employee) super.clone();
        // } catch (CloneNotSupportedException e) {
        // // Should never happen
        // throw new AssertionError();
        // }
    }

    @Override
    public String toString() {
        return super.toString() + " " + this.workId;
    }

    // CWE-495: Private Data Structure Returned From a Public Method
    public Employee getEmployee() {
        return this;
    }
}

public class Classes {
    public static void main(String[] args) throws Exception {
        Pattern pattern = Pattern.compile("^[0-9]{9}$"); // simple SSN validation


        Person p = new Person("Thomas Gray", "tcgray2", "888888888");
        // CWE-492: Use of Inner Class containing sensitive data
        Person.Student s = p.new Student(p.getName(), p.getID(), p.getSSN(), 3.5); // I don't want to EVER get the SSN
        System.out.println(s.toString());
        Person newPerson = new Employee("Thomas", "8828282", "898913909", "981y59018y");
        Person newerPerson = newPerson.clone();
        newerPerson.toString();
        System.out.println(newPerson.toString());

        // CWE-625: Permissive Regular Expression - avoid allowing SSN's that are not 9 numbers
        Matcher matcher = pattern.matcher(newPerson.getSSN());
        if (matcher.matches()) {
            System.out.println("The SSN has 9 numbers");
        }

        newPerson.setSSN("9108509187590187");

        // Avoiding CWE-187: Partial String Comparison -- make sure you compare entire strings (Java)
        if (newPerson.getID().equals(newerPerson.getID())) {
            System.out.println("The two people's work IDs match");
        }

        // CWE-486: Comparison of Classes by Name
        // if (p.getClass().equals("Student") - don't do this
        if (p.getClass() == Employee.class) { // - do this instead
            System.out.println(p.getName() + " is a employee");
        } else {
            System.out.println(p.getName() + " is not a employee");
        }

        Person testPerson = new Employee("TestName", "222", "3333333333", "111111111").getEmployee();
        Person testPerson2 = new Employee("TestName", "222", "3333333333", "111111111").getEmployee();
        
        // CWE-595: Comparison of Object References Instead of Object Contents 
        if (testPerson.equals(testPerson2)) {
            //should return false
            System.out.println("The two test people are equal");
        }
        System.out.println(testPerson.toString());
        // CWE-586: Explicit Call to Finalize()
    }
    // Avoiding CWE-586: Explicit Call to Finalize()
}