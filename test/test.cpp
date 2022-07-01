#include"connection_pool.h"
ConnPool *connpool = ConnPool::GetInstance();
int main(){
	Connection *con;
	Statement *state;
	ResultSet *result;
	con = connpool->GetConnection();
	cout<<"success"<<endl;
	delete result;
	delete state;
	connpool->ReleaseConnection(con);
	return 0;
}
