#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string generate_joke(std::string json)
{
	std::string joke;
	for(unsigned int i = 0; i < json.length(); i++)
	{
		if((json[i] == 'j') and \
		(json[i + 1] == 'o') and \
		(json[i + 2] == 'k') and \
		(json[i + 3] == 'e') and \
		(json[i + 4] == '"') and \
		(json[i + 5] == ':'))
		{
			for(unsigned int j = i + 8; j < json.length(); j++)
			{
				if(json[j] == '"') break;
				else joke.push_back(json[j]);
			}
		}
	}
	//joke = "Archeologists unearthed an old english dictionary dating back to the year 1236. It defined &quot;victim&quot; as &quot;one who has encountered Chuck Norris&quot;";
	for(unsigned int i = 0; i < joke.length(); i++)
	{
		if((joke[i] == '&') and \
		(joke[i + 1] == 'q') and \
		(joke[i + 2] == 'u') and \
		(joke[i + 3] == 'o') and \
		(joke[i + 4] == 't') and \
		(joke[i + 5] == ';'))
		{
			joke[i] = '"';
			joke.erase(joke.begin() + i + 1, joke.begin() + i + 6);
		}
	}
	return joke;
}

int main(int argc, char *argv[])
{
	std::string data;
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "http://api.icndb.com/jokes/random");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	std::cout << generate_joke(data) << std::endl;
	return 0;
}
