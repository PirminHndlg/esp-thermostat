bool toBoolean(String value) {
  if (value == "true") return true;
  else if (value == "TRUE") return true;
  else if (value == "True") return true;
  else if (value == "t") return true;
  else if (value == "1") return true;
  else if (value == "0") return false;
  else if (value == "false") return false;
  else if (value == "FALSE") return false;
  else if (value == "False") return false;
  else if (value == "f") return false;
  else return false;
}