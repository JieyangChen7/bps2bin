#include <adios2.h>

template <typename T>
std::vector<T> readBP(char * input_file, char * variable_name) {
	fprintf(stdout, "Reading file: %s\n", input_file);
  adios2::ADIOS ad;
	adios2::IO io = ad.DeclareIO("IO");
	io.SetEngine("BP4");
	adios2::Engine reader = io.Open(std::string(input_file)+".bp", adios2::Mode::Read);
	adios2::Variable<T> varT = io.InquireVariable<T>(std::string(variable_name));
	std::vector<T> u;
	reader.BeginStep();
	reader.Get<float>(varT, u, adios2::Mode::Sync);
	reader.EndStep();
	reader.Close();
	return u;
}

template <typename T>
void writefile(const char * output_file, size_t num_bytes, T * out_buff) {
  FILE * file = fopen(output_file, "w");
  fwrite(out_buff, 1, num_bytes, file);
  fclose(file);
}

int main(int argc, char *argv[]) {
	int i = 1;
	int num_input_file = atoi(argv[i++]);
	char ** input_file = new char *[num_input_file];
	for (int i = 0; i < num_input_file; i++) {
		input_file[i] = argv[i++];
	}
	char * output_file = argv[i++];
	char * variable_name = argv[i++];
	int dtype = atoi(argv[i++]);
	std::vector<size_t> shape;
	int D = atoi(argv[i++]);
	size_t n = 1;
	for (int d = 0; d < D; d++) {
	  shape.push_back(atoi(argv[i++]));
	  n *= shape[d];
	}

	if (dtype == 0) { 
		float * out_buff = new float[n*num_input_file];
		for (int i = 0; i < num_input_file; i++) { 
			std::vector<float> data = readBP<float>(input_file[i], variable_name);
			std::copy(data.begin(), data.end(), out_buff + i * n*sizeof(float));
		}
		writefile(output_file, n*sizeof(float)*num_input_file, out_buff);
	}
	return 0;
}

