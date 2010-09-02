
typedef enum _DownloadResult
{
	ENUM_DOWNLOAD_RESULT_SUCCESS,
	ENUM_DOWNLOAD_RESULT_FAILED,
	ENUM_DOWNLOAD_RESULT_CANCEL,
} ENUM_DOWNLOAD_RESULT;

enum
{
	NOTIFY_TYPE_GOT_REMOTE_FILENAME,				// ȡ��Զ��վ���ļ���, �������ص��ļ����ض���ʱ�ŷ��͸�֪ͨ��lpNotifyData Ϊ LPCTSTR ���͵��ļ����ַ���ָ��
	NOTIFY_TYPE_GOT_REMOTE_FILESIZE,				// ȡ��Զ��վ���ļ���С��lpNotifyData Ϊ int ���͵��ļ���С
	NOTIFY_TYPE_START_DOWNLOAD,						// ��ʼ���أ�lpNotifyData ����
	NOTIFY_TYPE_END_DOWNLOAD,						// �������أ�lpNotifyData Ϊ ENUM_DOWNLOAD_RESULT ���͵����ؽ��
	NOTIFY_TYPE_WILL_DOWNLOAD_SIZE,					// ������Ҫ���صĴ�С��lpNotifyData Ϊ int ���͵���Ҫ���صĴ�С
	NOTIFY_TYPE_THREAD_DOWNLOADED_SIZE,				// ĳ�߳������ص����ݴ�С��lpNotifyData Ϊ int ���͵������صĴ�С
};

typedef struct _DownloadNotifyPara
{
	int nIndex;
	UINT nNotityType;
	LPVOID lpNotifyData;
	LPVOID pDownloader;
} t_DownloadNotifyPara;

typedef void (*FUNC_CallBack) ( t_DownloadNotifyPara *pDownloadNotifyPara, WPARAM wParam );

class CDownloader {
private:
	bool			bStop;
	HANDLE			hThreadDownload;

	wstring			download_url;
	wstring			file_name;
	wstring			file_path;

	FUNC_CallBack	m_CallBack;
	WPARAM			m_wPrarm;

	static UINT DownloadThread(LPVOID pParam);

	std::wstring& wtrimRight(std::wstring &s, std::wstring sp);

	bool ParseURL(wstring url, wstring &HostName, wstring &FileName);

	DWORD __fastcall GetHttpFileSize(HINTERNET hRequest);

	wstring __fastcall GetHttpFileEtag(HINTERNET hRequest);

	SYSTEMTIME __fastcall GetHttpFileDateTime(HINTERNET hRequest);

	void HttpGetFile(wstring url, wstring path, wstring filename);

	void StartHttpDownload();

	void DoCallBack(int nIndex, UINT nNotityType, LPVOID lpNotifyData = NULL, LPVOID pDownloader = NULL);

	FILE * OpenInfoFile(wstring infofile, wstring etag, SYSTEMTIME last_time, DWORD file_size, long &download_size, bool rewrite);
	void CloseInfoFile(FILE *fpinfo, wstring infofile, DWORD file_size, DWORD download_size);
	void UpdateInfo(FILE *fpinfo, DWORD download_size);

	BOOL CheckDownloadFile(wstring filename, DWORD file_size, SYSTEMTIME last_time);

	void SetTimeStamp(wstring filename, SYSTEMTIME last_time);

public:

	CDownloader();
	~CDownloader();

	void SetCallBack(FUNC_CallBack callback, WPARAM wParam);

	void StartDownload(wstring url, wstring path, wstring filename);

	void StopDownload();
};
