#include "pch.h"
#include "AlgoMod.h"


/// <summary>
/// Performs CURL request to get body content of ids.txt.
/// </summary>
/// <remarks>Gathered IDs content is decrypted into plain text by <see cref"DecryptIDS(const std::string& encryptedText, const std::string& key)"/> and set to <see cref"rawIds"/></remarks>
void AlgoMod::CURLIDs() {
	CurlRequest req;
	req.url = "REDACTED";
	req.body = "";

	HttpWrapper::SendCurlJsonRequest(req, [&](int code, std::string result) {
		if (code == 200) {
			rawIds = DecryptIDS(result, "REDACTED");
		}
		else {
			LOG("Error: cURL ids failed");
		}
		});
}


/// <summary>
/// Performs CURL request for AlgoMod info.txt.
/// </summary>
/// <remarks>Gathered body is set to <see cref"rawInfo"/></remarks>
void AlgoMod::CURLInfo() {
	CurlRequest req;
	req.url = "REDACTED";
	req.body = "";

	HttpWrapper::SendCurlJsonRequest(req, [&](int code, std::string result) {
		if (code == 200) {
			rawInfo = result;
		}
		else {
			LOG("Error: cURL info failed");
		}
		});
}


/// <summary>
/// Connects to algorl.com to see if the client has internet and the domain is up. Also checks that pluginenabled.txt is true.
/// </summary>
/// <remarks>pluginenabled is a kill switch.</remarks>
void AlgoMod::IsInternetConnected() {
	CurlRequest req;
	req.url = "REDACTED";
	req.body = "";

	HttpWrapper::SendCurlJsonRequest(req, [&](int code, std::string result) {
		if (code != 200) {
			LOG("Error: You need internet access to use this mod(1)");
			isEnabled = false;
			internetIssue = true;
			return;
		}

		if (result != "true\n") {
			isEnabled = false;
			internetIssue = false;
			LOG("Error: Version Disabled!");
			return;
		}

		if (code == 200 && result == "true\n") {
			isEnabled = true;
			internetIssue = false;

			if (CallCommandOnce == false) {
				Commands();
				CallCommandOnce = true;
			}
		}
		});
}
