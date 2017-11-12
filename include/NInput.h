#ifndef					NINPUT_H
# define				NINPUT_H

#define					FUNC		void function();

class					NInput
{
 private:
  std::map<std::string, FUNC>		bind;
  
 public:
  NInput();
  ~NInput();

  void					addInput(std::string str, FUNC func);
  void					removeInput(std::string str);
  void					execInput(std::string str);
};

#endif			/* !NINPUT_H */
