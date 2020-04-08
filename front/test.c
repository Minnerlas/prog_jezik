int main(int argc, char** argv) {
	if (argc<9) {
		a >>= 3;
		printf("ASdjasdlkj\n");
		--a;
		goto asdasd;
		exit(1);
	} else if (a<3){
		asdasd();
	}

asdasd:
	return 123;

}

float limitedSquare(float x){
	/*
	 * returnsx-squared,butnevermorethan100
	 * */
	return (x<=-10.0||x>=10.0)?100:x*x;
}
