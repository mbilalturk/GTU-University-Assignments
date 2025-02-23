public class Person {
    private String name;
    private String surname;
    private String address;
    private String phone;
    private int ID;

    // Constructor of Person
    public Person(String _name, String _surname, String _address, String _phone, int _ID) {
        try {
            setName(_name);
            setSurname(_surname);
            setAddress(_address);
            setPhone(_phone);
            setID(_ID);
        }
        catch (Exception ignored) {
            // Do nothing
        }
    }

    public Person() {
        this("Unknown", "Unknown", "Unkown", "Unkown", 0);
    }

    public String getName() {
        return name;
    }
    private void setName(String _name) throws Exception {
        if(_name == null || _name.isEmpty())
            throw new Exception("String cannot be empty!");
        this.name = _name;
    }

    public String getSurname() {
        return surname;
    }
    private void setSurname(String _surname) throws Exception {
        if(_surname == null || _surname.isEmpty())
            throw new Exception("String cannot be empty!");
        this.surname = _surname;
    }

    public String getAddress() {
        return address;
    }
    private void setAddress(String _address) throws Exception {
        if(_address == null ||_address.isEmpty())
            throw new Exception("String cannot be empty!");
        this.address = _address;
    }

    public String getPhone() {
        return phone;
    }
    private void setPhone(String _phone) throws Exception {
        if(_phone == null ||_phone.isEmpty())
            throw new Exception("String cannot be empty!");
        this.phone = _phone;
    }

    public int getID() {
        return ID;
    }
    private void setID(int _ID) throws Exception {
        if(_ID <= 0)
            throw new Exception("ID cannot be negative!");
        this.ID = _ID;
    }
}
