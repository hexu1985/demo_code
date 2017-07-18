struct User {
    1: string uid,  
    2: string uname,  
    3: bool usex,  
    4: i16 uage,  
}

struct UserQuery {
    1: string uid,
}

service UserService {
    void add(1: User u),  
    User get(1: UserQuery qry),  
} 

