class Person implements Cloneable {
    private String name;
    private String ID;
    private String SSN;

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

    public void setSSN(String SSN) {
        this.SSN = SSN;
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
        Person p = new Person("Thomas Gray", "tcgray2", "888888888");
        // CWE-492: Use of Inner Class containing sensitive data
        Person.Student s = p.new Student(p.getName(), p.getID(), p.getSSN(), 3.5); // I don't want to EVER get the SSN
        System.out.println(s.toString());
        Person newPerson = new Employee("Thomas", "8828282", "981y59018y", "89889190");
        Person newerPerson = newPerson.clone();
        newerPerson.toString();
        System.out.println(newPerson.toString());

        Person testPerson = new Employee("TestName", "222", "3333333333", "111111111").getEmployee();
        System.out.println(testPerson.toString());
        // CWE-586: Explicit Call to Finalize()
    }
}